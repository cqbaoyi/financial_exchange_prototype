#include<iostream>
#include<stdexcept>
#include<string>
#include<tuple>

#include"orderBook.hpp"

void orderPool::reserve(orderIdType maxOrderId)
{
    m_orders.reserve(maxOrderId);
}

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

void orderPool::modifyQuantity(orderIdType orderId, orderQuantityType quantity)
{
    m_orders[orderId].set_quantity(quantity);
}

const order& orderPool::operator[](orderIdType orderId)
{
    return m_orders[orderId];
}

orderBook::orderBook(lib::symbol symbol, orderPool& op)
{
    m_orderPool = std::make_shared<orderPool>(op);
}

template <>
askBookType& orderBook::getMap() { return m_asks; }

template <>
bidBookType& orderBook::getMap() { return m_bids; }

template<>
bool orderBook::priceCross(const Price4& p, const askBookType& askBook) const { return (*askBook.begin()).first <= p; };

template<>
bool orderBook::priceCross(const Price4& p, const bidBookType& bidBook) const { return (*bidBook.begin()).first >= p; };
