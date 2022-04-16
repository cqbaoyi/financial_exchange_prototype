#pragma once

#include<unordered_map>

#include"order.hpp"

class orderPool
{
private:
    std::unordered_map<orderIdType, order> m_orders;    // orderId -> order

public:
    orderPool() = default;
    explicit orderPool(orderIdType maxOrderId);

    // Add an order, which has a positive remaining quantity after matching, to the pool
    void add(const order& od);

    // Remove an order from the pool
    void remove(orderIdType orderId);

    // Modify the quantity of an existing order.
    void modifyQuantity(orderIdType orderId, orderQuantityType quantity);

    const order& operator[](orderIdType orderId);
};
