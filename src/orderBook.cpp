#include<iostream>
#include<stdexcept>
#include<string>
#include<tuple>

#include"orderBook.hpp"

void orderPool::add(const order& od)
{
    try
    {
        orderIdType orderId = od.get_orderId();
        m_orders[orderId] = od;
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
        m_orders.erase(orderId);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const order& orderPool::operator[](orderIdType orderId)
{
    return m_orders[orderId];
}

orderBook::orderBook(const orderPool& op)
{
    m_orderPool = std::make_unique<orderPool>(op);
}

template <>
askBookType& orderBook::getMap() { return m_asks; }

template <>
bidBookType& orderBook::getMap() { return m_bids; }

/*
void orderBook::add(orderIdType orderId)
{
    const order& od = (*m_orderPool)[orderId];
    lib::orderSide orderSide = od.get_orderSide();

    if (orderSide == lib::orderSide::ASK)
        //_add<askBookType>(orderId);
        auto& curBook = getMap<askBookType>();
    else
        //_add<bidBookType>(orderId);
        auto& curBook = getMap<bidBookType>();
}

void orderBook::remove(orderIdType orderId)
{
    const order& od = (*m_orderPool)[orderId];
    lib::orderSide orderSide = od.get_orderSide();

    //if (orderSide == lib::orderSide::ASK)
    //    _remove<askBookType>(orderId);
    //else
    //    _remove<bidBookType>(orderId);
}
*/