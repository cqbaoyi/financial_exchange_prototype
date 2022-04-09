#pragma once

#include"orderBook.hpp"

class matchingEngine
{
private:
    std::vector<std::unique_ptr<orderBook>> m_orderBooks;

public:
    matchingEngine() = default;
    explicit matchingEngine(orderIdType maxOrderId);

    // Serve an incoming order by orderId and return a Boolean
    // TODO: 
    // 1) integrate the market data publisher
    // 2) multithreading
    void serve(order& od);
};