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
    std::vector<order> m_orderPool;    // orderId -> order

public:
    orderPool() = default;
    
    // add an order, which has a positive remaining quantity after matching, to the pool
    void add(const order& ord);

    // remove an order from the pool
    void remove(orderIdType orderId);

    // TODO: modify an order's quantity in the pool
    // The modified order obtains a new timeStamp and appends to the end of linked list of the price level.
    void modify(orderIdType orderId, int64_t quantity);
};

class orderBook
{
private:
    std::map<Price4, std::list<orderIdType>> m_asks;    // price -> linked list of orderId
    std::map<Price4, std::list<orderIdType>, std::greater<Price4>> m_bids;    // price -> linked list of orderId
    std::vector<std::list<orderIdType>::iterator> m_orderIt;    // orderId -> linked list iterator
public:
    orderBook() = default;
    orderBook(order od);
};