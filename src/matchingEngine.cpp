#include"matchingEngine.hpp"

void matchingEngine::initialize()
{
    m_orderPool.reserve(m_maxOrderId);

    // Each symbol has an independent order book.
    m_orderBooks.reserve(lib::N_symbol);
    for (size_t i = 0; i < lib::N_symbol; ++i)
        m_orderBooks.emplace_back(std::make_unique<orderBook>(static_cast<lib::symbol>(i), m_orderPool));
}

void matchingEngine::serve(order& od)
{
    lib::symbol symbol = od.get_symbol();
    bool isAskOrder = od.get_orderSide() == lib::orderSide::ASK;
    
    orderQuantityType remaining_quantity = 0;
    if (isAskOrder)
        remaining_quantity = (*m_orderBooks[static_cast<uint32_t>(symbol)]).match<bidBookType>(od);
    else
        remaining_quantity = (*m_orderBooks[static_cast<uint32_t>(symbol)]).match<askBookType>(od);

    od.set_quantity(remaining_quantity);
    if (isAskOrder)
        (*m_orderBooks[static_cast<uint32_t>(symbol)]).add<askBookType>(od);
    else
        (*m_orderBooks[static_cast<uint32_t>(symbol)]).add<bidBookType>(od);

}