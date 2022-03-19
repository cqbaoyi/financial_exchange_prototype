#pragma once

#include<chrono>
#include<fstream>
#include<iostream>
#include<random>

#include"enum.hpp"
class Price4
{
private:
    static constexpr uint8_t Scale4 = 4U;
    static constexpr int64_t PowScale4 = 10000LL;
    int64_t m_unscaled;

public:
    Price4() = default;

    explicit Price4(long unscaled): m_unscaled(unscaled) {};

    // Convert from string
    explicit Price4(const std::string& s);

    // Convert to string
    std::string to_str() const;

    inline int64_t unscaled() const { return m_unscaled; };

    // Overloading operators
    inline bool operator<(const Price4& rhs) const;
    inline bool operator>(const Price4& rhs) const;
    inline bool operator<=(const Price4& rhs) const;
    inline bool operator>=(const Price4& rhs) const; 
};
class order
{
private:
    // A global incrementing order id
    static uint64_t globalOrderId;

    uint64_t m_orderId;
    std::chrono::time_point<std::chrono::system_clock> m_timeStamp;
    orderType m_orderType;
    ticker m_symbol; 
    orderSide m_orderSide;
    int64_t m_quantity;
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

// The orderGenerator now only generates the orders into one single file.
class orderGenerator
{
private:
    std::chrono::time_point<std::chrono::system_clock> m_timeStamp;
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int64_t> dist;

public:
    orderGenerator() = default;
    orderGenerator(std::chrono::time_point<std::chrono::system_clock> timeStamp);
    void run();
};