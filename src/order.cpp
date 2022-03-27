#include<iostream>

#include"order.hpp"

void order::print_info()
{
    std::cout << std::chrono::duration_cast<Seconds>(m_timeStamp.time_since_epoch()).count() << "\n";
    std::cout << m_orderId << "\n";
    std::cout << m_orderType << "\n";
    std::cout << m_symbol << "\n";
    std::cout << m_orderSide << "\n";
    std::cout << m_quantity << "\n";
    std::cout << m_limitPrice << "\n";
}

void to_json(json& j, const order& od)
{
    j = json{
        {"timeStamp", std::chrono::duration_cast<Seconds>(od.get_time().time_since_epoch()).count()}, 
        {"orderId", od.get_orderId()}, 
        {"orderType", od.get_orderType()}, 
        {"symbol", od.get_symbol()}, 
        {"orderSide", od.get_orderSide()}, 
        {"quantity", od.get_quantity()}, 
        {"price", od.get_Price4().to_str()}, 
    };
}

void from_json(const json& j, order& od)
{
    od.set_time() = Clock::time_point(Seconds(j.at("timeStamp")));
    j.at("orderId").get_to(od.set_orderId());
    j.at("orderType").get_to(od.set_orderType());
    j.at("symbol").get_to(od.set_symbol());
    j.at("orderSide").get_to(od.set_orderSide());
    j.at("quantity").get_to(od.set_quantity());
    j.at("price").get_to(od.set_Price4());
}