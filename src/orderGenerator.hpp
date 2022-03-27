#pragma once

#include<chrono>
#include<random>

#include"enum.hpp"
#include"order.hpp"


// The orderGenerator is used to generate orders but not required by this project.
// It generates the orders and write into one single json file.
class orderGenerator
{
private:
    static constexpr int64_t PowScale4 = 10000LL;

    // A global incrementing order id
    static orderIdType globalOrderId;

    static double cancelRatio;

    std::string m_fileName;
    lib::symbol m_symbol;    // Only one symbol for now
    std::chrono::time_point<Clock> m_t_start, m_t_end;

    std::random_device rd;
    std::mt19937 m_gen;
    std::uniform_real_distribution<double> m_distReal;
    std::binomial_distribution<int64_t> m_distQuantity;
    std::lognormal_distribution<double> m_distPrice;
    std::uniform_int_distribution<orderIdType> m_distOrderId;

    // Randomly generate: orderId (cancel), orderType, orderSide, quantity, and limit price
    inline orderIdType genCancelOrderId();
    inline lib::orderType genOrderType();
    inline lib::orderSide genOrderSide();
    inline int64_t genQuantity();
    inline int64_t genPrice();

public:
    orderGenerator() = default;
    orderGenerator(lib::symbol symbol);
    void run();
};