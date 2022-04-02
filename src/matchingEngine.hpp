#pragma once

#include"orderBook.hpp"

class matchingEngine
{
private:
    static const orderIdType m_maxOrderId = 1'000'000'000;

    orderPool m_orderPool;
    std::vector<std::unique_ptr<orderBook>> m_orderBooks;
public:
    matchingEngine() = default;

    void initialize();

    // Serve an incoming order by orderId and return a Boolean
    // TODO: 
    // 1) integrate the market data publisher
    // 2) multithreading
    void serve(order& od);
};