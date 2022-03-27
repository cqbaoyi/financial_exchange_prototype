#include<iostream>
#include<stdexcept>
#include<string>

#include"orderBook.hpp"

void orderPool::add(const order& od)
{
    try
    {
        orderIdType orderId = od.get_orderId();
        if (orderId != m_orderPool.size())
            throw std::runtime_error("orderPool: unexpected orderId " + std::to_string(orderId) + " to be added.");
        m_orderPool.emplace_back(od);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void orderPool::remove(orderIdType orderId)
{
    try
    {
        // The orderId is effectively invalid. Assign a dummy order which should not even be accessed any more.
        m_orderPool[orderId] = order();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}