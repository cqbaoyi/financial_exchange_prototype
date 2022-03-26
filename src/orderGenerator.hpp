#pragma once

#include<chrono>
#include<random>

#include"enum.hpp"


// The orderGenerator now only generates the orders into one single file.
class orderGenerator
{
private:
    static constexpr int64_t PowScale4 = 10000LL;

    // A global incrementing order id
    static uint64_t globalOrderId;

    // Limit order placement by high-frequency traders
    static double cancelRatio;

    std::string m_fileName;
    lib::symbol m_symbol;    // Only one symbol for now
    std::chrono::time_point<std::chrono::system_clock> m_t_start, m_t_end;

    std::random_device rd;
    std::mt19937 m_gen;
    std::lognormal_distribution<double> m_dist;

    // Generate the stock price from the random generator of integer type
    inline int64_t genPrice();

public:
    orderGenerator() = default;
    orderGenerator(const std::string& fileName);
    void run();
};