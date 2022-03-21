#pragma once

#include<chrono>
#include<list>
#include<map>
#include<string>
#include<vector>
#include<unordered_map>

#include"enum.hpp"
#include"orderGenerator.hpp"

class orderPool
{
private:
    std::vector<order> m_orderPool;    // orderId -> order

public:
    orderPool() = default;
    
    // add an order, which has a positive remaining quantity after matching, to the pool
    void add(const order& ord);

    // remove an order from the pool
    void remove(uint64_t orderId);

    // modify an order's quantity in the pool
    void modify(uint64_t orderId, int64_t quantity);
};

class orderBook
{
private:
    std::map<Price4, std::list<uint64_t>> m_asks;    // price -> linked list of orderId
    std::map<Price4, std::list<uint64_t>, std::greater<Price4>> m_bids;    // price -> linked list of orderId
    std::vector<std::list<uint64_t>::iterator> m_orderIt;    // orderId -> linked list iterator
public:
    orderBook() = default;
    orderBook(order od);
};