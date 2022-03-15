#pragma once

#include<chrono>
#include<string>
#include<map>
#include"enum.hpp"

class Price4
{
private:
    long m_unscaled;

public:
    Price4() = default;
    long unscaled() { return m_unscaled; };

    explicit Price4(long unscaled): m_unscaled(unscaled) {};

    // Convert from string
    explicit Price4(const std::string& str);

    // Convert to string
    std::string to_str() const;  
};

class order
{
private:
    // A global incrementing order id
    static unsigned int globalOrderId;

    unsigned int m_orderId;
    std::chrono::time_point<std::chrono::system_clock> m_timeStamp;
    orderType m_orderType;
    ticker m_symbol; 
    orderSide m_orderSide;
    int m_quantity;
    Price4 m_limitPrice;

public:
    order() = default;
    order(std::chrono::time_point<std::chrono::system_clock> timeStamp, orderType oT, ticker symbol, orderSide os, int quantity, Price4 limitPrice): 
        m_orderId(globalOrderId++), 
        m_timeStamp(timeStamp),
        m_orderType(oT),
        m_symbol(symbol),
        m_orderSide(os),
        m_quantity(quantity),
        m_limitPrice(limitPrice)
        {};
};

class orderBook
{
private:
    std::map<Price4, int> asks;
    std::map<Price4, int, std::greater<Price4>> bids;
public:
    orderBook() = default;
    orderBook(order od);
};