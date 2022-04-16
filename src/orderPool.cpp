#include"orderPool.hpp"


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
