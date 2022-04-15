#pragma once

#include<chrono>
#include<list>
#include<map>
#include<string>
#include<vector>
#include<unordered_map>

#include"enum.hpp"
#include"Event.hpp"
#include"Observable.hpp"
#include"order.hpp"
#include"Price4.hpp"

class orderPool
{
private:
    std::unordered_map<orderIdType, order> m_orders;    // orderId -> order

public:
    orderPool() = default;
    explicit orderPool(orderIdType maxOrderId);

    // Add an order, which has a positive remaining quantity after matching, to the pool
    void add(const order& od);

    // Remove an order from the pool
    void remove(orderIdType orderId);

    // Modify the quantity of an existing order.
    void modifyQuantity(orderIdType orderId, orderQuantityType quantity);

    const order& operator[](orderIdType orderId);
};

typedef std::map<Price4, std::list<orderIdType>> askBookType;
typedef std::map<Price4, std::list<orderIdType>, std::greater<Price4>> bidBookType;
// askBookType::iterator is of the same type as bidBookType::iterator
typedef std::unordered_map<orderIdType, askBookType::iterator> orderId2BookIt;    

class orderBook
{
private:
    askBookType m_asks;    // price -> linked list of orderId
    bidBookType m_bids;    // price -> linked list of orderId  
    std::unordered_map<orderIdType, std::list<orderIdType>::iterator> m_orderIt;    // orderId -> order iterator
    orderId2BookIt m_orderId2AskBookIt;    // orderId -> ask book iterator
    orderId2BookIt m_orderId2BidBookIt;    // orderId -> bid book iterator
    lib::symbol m_symbol;
    std::unique_ptr<orderPool> m_orderPool;

    template<typename T>
    T& getBook();

    template<typename T>
    orderId2BookIt& getOrderId2BookIt();

    // Determine whether there is a price cross based on T
    template<typename T>
    bool priceCross(const Price4& p, const T& book) const;

public:
    orderBook() = default;
    explicit orderBook(lib::symbol symbol, orderIdType maxOrderId);

    // Match an order against the other side of the book.
    // Return the remaining quantity if not fully filled.
    template<typename T>
    orderQuantityType match(const order& od);

    // A new order, after being matched, is added to the book.
    // O(log M) where M is the number of price levels.
    template<typename T>
    void add(const order& od);

    // A cancel order is received or an existing order on the book is filled.
    // Return 1) whether a price level is to remove, 2) Price4, and 3) quantity.
    // O(1)
    template<typename T>
    bool remove(orderIdType orderId);
};

template<typename T>
orderQuantityType orderBook::match(const order& od)
{
    auto& curBook = getBook<T>();
    orderQuantityType remaining_quantity = od.get_quantity();
    const Price4& p = od.get_Price4();

    while(remaining_quantity && !curBook.empty() && priceCross(p, curBook))
    {
        auto cur_p = (*curBook.begin()).first;
        auto& orders_this_level = (*curBook.begin()).second;
        std::list<orderIdType>::iterator it = orders_this_level.begin();

        while(remaining_quantity && it != orders_this_level.end())
        {
            orderQuantityType q = (*m_orderPool)[*it].get_quantity();
            if (q <= remaining_quantity)
            {
                remaining_quantity -= q;
                bool removed = remove<T>(*it);
                if (removed)    // The price level is removed
                {
                    break;
                }
                ++it;
            }
            else
            {
                q -= remaining_quantity;
                remaining_quantity = 0;
                (*m_orderPool).modifyQuantity(*it, q);
            }
        }
    }

    return remaining_quantity;
}

template<typename T>
void orderBook::add(const order& od)
{
    orderIdType orderId = od.get_orderId();
    // Add to the order pool
    (*m_orderPool).add(od);

    const Price4& p = od.get_Price4();
    auto& curBook = getBook<T>();
    auto& order2BookMap = getOrderId2BookIt<T>();

    std::list<orderIdType>::iterator it;
    typename T::iterator price_it = curBook.find(p);
    if (price_it == curBook.end())    // A new top price level
    {
        auto [new_price_it, success] = curBook.insert({p, std::list<orderIdType>{orderId}});
        it = new_price_it->second.begin();
        order2BookMap[orderId] = new_price_it;
    }
    else
    {
        it = price_it->second.insert(price_it->second.end(), orderId);
        order2BookMap[orderId] = price_it;
    }

    m_orderIt[orderId] = it;
}

template<typename T>
bool orderBook::remove(orderIdType orderId)
{
    bool erase_price_level = false;

    const order& od = (*m_orderPool)[orderId];
    const Price4& p = od.get_Price4();
    auto& curBook = getBook<T>();

    auto& order2BookMap = getOrderId2BookIt<T>();
    {
        std::list<orderIdType>::iterator it = m_orderIt[orderId];
        auto price_it = order2BookMap[orderId];
        price_it->second.erase(it);
        if (price_it->second.empty())    // No orders at this price level
        {
            curBook.erase(price_it);
            erase_price_level = true;
        }
        order2BookMap.erase(orderId);
        m_orderIt.erase(orderId);
    }

    (*m_orderPool).remove(orderId);

    return erase_price_level;
}