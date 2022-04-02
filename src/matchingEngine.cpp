#include"matchingEngine.hpp"

matchingEngine::matchingEngine(orderIdType maxOrderId)
{
    m_orderPool.reserve(maxOrderId);

    // Each symbol has an independent order book.
    m_orderBooks.reserve(lib::N_symbol);
    for (size_t i = 0; i < lib::N_symbol; ++i)
        m_orderBooks.emplace_back(std::make_unique<orderBook>(static_cast<lib::symbol>(i), m_orderPool));
}

void matchingEngine::serve(order& od)
{
    lib::symbol symbol = od.get_symbol();
    bool isCancel = od.get_orderType() == lib::orderType::CANCEL;
    bool isAskOrder = od.get_orderSide() == lib::orderSide::ASK;
    
    if (isCancel)
    {
        orderIdType orderId = od.get_orderId();
        if (isAskOrder)
            (*m_orderBooks[static_cast<uint32_t>(symbol)]).remove<askBookType>(orderId);
        else
            (*m_orderBooks[static_cast<uint32_t>(symbol)]).remove<bidBookType>(orderId); 
    }
    else
    {
        orderQuantityType remaining_quantity = 0;
        if (isAskOrder)    // Match against the other side of the book
            remaining_quantity = (*m_orderBooks[static_cast<uint32_t>(symbol)]).match<bidBookType>(od);
        else
            remaining_quantity = (*m_orderBooks[static_cast<uint32_t>(symbol)]).match<askBookType>(od);

        od.set_quantity(remaining_quantity);
        if (isAskOrder)
            (*m_orderBooks[static_cast<uint32_t>(symbol)]).add<askBookType>(od);
        else
            (*m_orderBooks[static_cast<uint32_t>(symbol)]).add<bidBookType>(od);
    }
}