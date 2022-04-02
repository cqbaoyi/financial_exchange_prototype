#include<fstream>
#include<iostream>
#include<nlohmann/json.hpp>

#include"order.hpp"
#include"orderGenerator.hpp"

/*********************************

orderGenerator implementation

*********************************/

using namespace std::chrono_literals;

// Set the initial global order ID to 0
orderIdType orderGenerator::globalOrderId = 0;

// Table 1 from A. Subrahmanyam and H. Zheng, 2016, Limit order placement by high-frequency traders
// About half of the orders are cancel orders.
double orderGenerator::cancelRatio = 0.5;

orderGenerator::orderGenerator(lib::symbol symbol): m_symbol(symbol)
{
    m_fileName = "orders_" + lib::symbolStr[static_cast<uint32_t>(symbol)] + ".json";

    m_gen = std::mt19937(rd());
    m_distReal = std::uniform_real_distribution<double>(0.0, 1.0);
    m_distQuantity = std::binomial_distribution<int64_t>(2000, 0.5);
    m_distPrice = std::lognormal_distribution<double>(5.0, 0.1);
    
    // The orders start to generate at 9:30am EST and ends at 4:00pm EST.
    // The starting time does not really matter in this project.
    m_t_start = Clock::now();
    m_t_end = m_t_start + std::chrono::hours(6) + std::chrono::minutes(30);
    //const std::time_t t_s = Clock::to_time_t(m_t_start);
    //const std::time_t t_e = Clock::to_time_t(m_t_end);
    //std::cout << std::put_time(std::localtime(&t_s), "%F %T.") << std::endl;
    //std::cout << std::put_time(std::localtime(&t_e), "%F %T.") << std::endl;
}

inline lib::orderType orderGenerator::genOrderType()
{
    return m_distReal(m_gen) < cancelRatio? lib::orderType::CANCEL: lib::orderType::NEW;
}

inline lib::orderSide orderGenerator::genOrderSide()
{
    // Assume half of the orders are bid orders.
    return m_distReal(m_gen) < 0.5? lib::orderSide::ASK: lib::orderSide::BID;
}

inline orderQuantityType orderGenerator::genQuantity()
{
    return m_distQuantity(m_gen);
}

inline int64_t orderGenerator::genPrice()
{
    return static_cast<int64_t>(m_distPrice(m_gen) * PowScale4);
}

inline orderIdType orderGenerator::genCancelOrderId()
{
    // The cancel order id should be an used order id.
    m_distOrderId = std::uniform_int_distribution<orderIdType>(0, globalOrderId - 1);
    return m_distOrderId(m_gen);
}

void orderGenerator::run()
{
    std::fstream f(m_fileName, std::ios::out);

    order myOrder;
    // For simplicity, generate one order per second
    for (auto t = m_t_start; t <= m_t_end; t += 1s)
    {
        lib::orderType orderType = genOrderType();
        if (orderType == lib::orderType::NEW)
            myOrder = order(t, globalOrderId++, orderType, m_symbol, genOrderSide(), genQuantity(), genPrice());
        else
            myOrder = order(t, genCancelOrderId(), orderType);
        json j = myOrder;
        f << j << std::endl;
    }
}