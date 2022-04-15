#include<iostream>
#include<stdexcept>
#include<string>
#include<tuple>

#include"orderBook.hpp"

/*****************************************************************
 * 
 * orderPool implementation
 * 
 *****************************************************************/

orderPool::orderPool(orderIdType maxOrderId)
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

/*****************************************************************
 * 
 * orderBook implementation
 * 
 *****************************************************************/

orderBook::orderBook(lib::symbol symbol, orderIdType maxOrderId)
{
    m_orderPool = std::make_unique<orderPool>(maxOrderId);
}

template <>
askBookType& orderBook::getBook() { return m_asks; }

template <>
bidBookType& orderBook::getBook() { return m_bids; }

//template<>
//order2askBookType& orderBook::getOrder2BookMap() { return m_order2askBook; }

// TODO: specialization redefinition error
//template<>
//order2bidBookType& orderBook::getOrder2BookMap() { return m_order2bidBook; }

template<>
orderId2BookIt& orderBook::getOrderId2BookIt<askBookType>(){ return m_orderId2AskBookIt; }

template<>
orderId2BookIt& orderBook::getOrderId2BookIt<bidBookType>(){ return m_orderId2BidBookIt; }

template<>
bool orderBook::priceCross(const Price4& p, const askBookType& askBook) const { return (*askBook.begin()).first <= p; };

template<>
bool orderBook::priceCross(const Price4& p, const bidBookType& bidBook) const { return (*bidBook.begin()).first >= p; };
