#pragma once

#include<chrono>
#include<list>
#include<map>
#include<string>
#include<vector>
#include<unordered_map>

#include"enum.hpp"
#include"order.hpp"
#include"Price4.hpp"

class orderPool
{
private:
    std::unordered_map<orderIdType, order> m_orders;    // orderId -> order

public:
    orderPool() = default;
    
    void reserve(orderIdType maxOrderId);

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
class orderBook
{
private:
    askBookType m_asks;    // price -> linked list of orderId
    bidBookType m_bids;    // price -> linked list of orderId  
    std::unordered_map<orderIdType, std::list<orderIdType>::iterator> m_orderIt;    // orderId -> linked list iterator
    lib::symbol m_symbol;
    std::shared_ptr<orderPool> m_orderPool;

    template<typename T>
    T& getMap();

    // Determine whether there is a price cross based on T
    template<typename T>
    bool priceCross(const Price4& p, const T& book) const;

public:
    orderBook() = default;
    orderBook(lib::symbol symbol, orderPool& op);

    // Match an order against the other side of the book.
    // Return the remaining quantity if not fully filled.
    template<typename T>
    orderQuantityType match(const order& od);

    // A new order, after being matched, is added to the book.
    // If it is a new price level, O(log M) where M is the number of price levels. Otherwise, O(1).
    template<typename T>
    void add(const order& od);

    // A cancel order is received or an existing order on the book is filled.
    // O(1)
    template<typename T>
    void remove(orderIdType orderId);
};

template<typename T>
orderQuantityType orderBook::match(const order& od)
{
    auto& curBook = getMap<T>();
    orderQuantityType remaining_quantity = od.get_quantity();
    const Price4& p = od.get_Price4();

    while(remaining_quantity && !curBook.empty() && priceCross(p, curBook))
    {
        auto& orders_this_level = (*curBook.begin()).second;
        auto it = orders_this_level.begin();
        while(remaining_quantity && it != orders_this_level.end())
        {
            // TODO: keep track of the filled prices and use them for the market data publisher
            orderQuantityType q = (*m_orderPool)[*it].get_quantity();
            if (q <= remaining_quantity)
            {
                remaining_quantity -= q;
                remove<T>(*it);
                ++it;
            }
            else
            {
                q -= remaining_quantity;
                remaining_quantity = 0;
                (*m_orderPool).modifyQuantity(*it, q);
            }
        }
        if (it == orders_this_level.end())   // Erase the price level
            curBook.erase(curBook.begin());
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
    auto& curBook = getMap<T>();

    std::list<orderIdType>::iterator it;
    if (curBook.find(p) == curBook.end())
    {
        curBook.insert({p, std::list<orderIdType>{orderId}});
        it = curBook[p].begin();
    }
    else
    {
        auto& l = curBook[p];
        it = l.insert(l.end(), orderId);
    }

    m_orderIt[orderId] = it;
}

template<typename T>
void orderBook::remove(orderIdType orderId)
{
    const order& od = (*m_orderPool)[orderId];
    const Price4& p = od.get_Price4();

    auto& curBook = getMap<T>();

    std::list<orderIdType>::iterator it = m_orderIt[orderId];
    curBook[p].erase(it);
    // Do not erase the price level

    m_orderIt.erase(orderId);
    (*m_orderPool).remove(orderId);
}