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
#include"orderPool.hpp"
#include"Price4.hpp"


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
    std::shared_ptr<orderPool> m_orderPool;

    template<typename T>
    T& getBook();

    template<typename T>
    orderId2BookIt& getOrderId2BookIt();

    template<typename T>
    lib::orderSide getCurBookSide();

    // Determine whether there is a price cross based on T
    template<typename T>
    bool priceCross(const Price4& p, const T& book) const;

public:
    orderBook() = default;
    explicit orderBook(lib::symbol symbol, std::shared_ptr<orderPool> op): m_orderPool(op)
    {}

    // Match an order against the other side of the book.
    // Return the remaining quantity if not fully filled.
    template<typename T>
    orderQuantityType match(const order& od, EventBlotter& eventBlotter);

    // A new order, after being matched, is added to the book.
    // O(log M) where M is the number of price levels.
    template<typename T>
    void add(const order& od, EventBlotter& eventBlotter);

    // A cancel order is received or an existing order on the book is filled.
    // Return 1) whether a price level is to remove, 2) Price4, and 3) quantity.
    // O(1)
    template<typename T>
    bool remove(orderIdType orderId, EventBlotter& eventBlotter);
};

template<typename T>
orderQuantityType orderBook::match(const order& od, EventBlotter& eventBlotter)
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
                bool removed = remove<T>(*it, eventBlotter);
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
void orderBook::add(const order& od, EventBlotter& eventBlotter)
{
    lib::orderSide bookSide = getCurBookSide<T>();
    orderIdType orderId = od.get_orderId();
    orderQuantityType orderQuantity = od.get_quantity();
    // Add to the order pool
    (*m_orderPool).add(od);

    const Price4& p = od.get_Price4();
    auto& curBook = getBook<T>();
    auto& order2BookMap = getOrderId2BookIt<T>();

    std::list<orderIdType>::iterator it;
    typename T::iterator price_it = curBook.find(p);
    bool newPriceLevel = price_it == curBook.end();
    if (newPriceLevel)    // A new price level
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

    // The event is either ADD or MODIFY.
    eventBlotter.addEvent(Event(newPriceLevel? lib::action::ADD: lib::action::MODIFY, p, orderQuantity, bookSide));

    m_orderIt[orderId] = it;
}

template<typename T>
bool orderBook::remove(orderIdType orderId, EventBlotter& eventBlotter)
{
    bool erase_price_level = false;

    lib::orderSide bookSide = getCurBookSide<T>();
    const order& od = (*m_orderPool)[orderId];
    orderQuantityType orderQuantity = od.get_quantity();
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

    // The event is either DELETE or MODIFY.
    eventBlotter.addEvent(Event(erase_price_level? lib::action::DELETE: lib::action::MODIFY, p, orderQuantity, bookSide));

    return erase_price_level;
}