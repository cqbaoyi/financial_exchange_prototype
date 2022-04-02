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
    
    // add an order, which has a positive remaining quantity after matching, to the pool
    void add(const order& ord);

    // remove an order from the pool
    void remove(orderIdType orderId);

    // TODO: modify an order's quantity in the pool
    // The modified order obtains a new timeStamp and appends to the end of linked list of the price level.
    void modify(orderIdType orderId, int64_t quantity);

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

    // An orderBook obj is associated with an orderPool obj.
    std::unique_ptr<orderPool> m_orderPool;

    template<typename T>
    T& getMap();

public:
    orderBook() = default;
    orderBook(const orderPool& op);

    // If it is a new price level, O(log M) where M is the number of price levels.
    // If it is not, O(1).
    template<typename T>
    void add(const order& od);

    // O(1)
    template<typename T>
    void remove(orderIdType orderId);
};

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
        it = curBook.insert({p, std::list<orderIdType>{orderId}});
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
    // Do not erase the price level though

    m_orderIt.erase(orderId);
    (*m_orderPool).remove(orderId);
}