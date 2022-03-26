#include<fstream>
#include<iostream>
#include<nlohmann/json.hpp>

#include"order.hpp"
#include"orderGenerator.hpp"

using json = nlohmann::json;

/*********************************

orderGenerator implementation

*********************************/

// Set the initial global order ID to 0
uint64_t orderGenerator::globalOrderId = 0;

// Table 1 from A. Subrahmanyam and H. Zheng, 2016, Limit order placement by high-frequency traders
// About half of the orders are cancel orders.
double orderGenerator::cancelRatio = 0.5;

orderGenerator::orderGenerator(const std::string& fileName): m_fileName(fileName)
{
    m_gen = std::mt19937(rd());
    m_dist = std::lognormal_distribution<double>(5.0, 0.1);
    m_symbol = lib::symbol::MSFT;
    
    // The orders start to generate at 9:30am EST and ends at 4:00pm EST.
    // The starting time does not really matter in this project.
    m_t_start = std::chrono::system_clock::now();
    m_t_end = m_t_start + std::chrono::hours(6) + std::chrono::minutes(30);
    const std::time_t t_s = std::chrono::system_clock::to_time_t(m_t_start);
    const std::time_t t_e = std::chrono::system_clock::to_time_t(m_t_end);
    std::cout << std::put_time(std::localtime(&t_s), "%F %T.") << std::endl;
    std::cout << std::put_time(std::localtime(&t_e), "%F %T.") << std::endl;
}

inline int64_t orderGenerator::genPrice()
{
    return static_cast<int64_t>(m_dist(m_gen)) * PowScale4;
}

void orderGenerator::run()
{
    std::fstream f(m_fileName, std::ios::out);

    int64_t unscaled_price = genPrice();
    order myOrder(std::chrono::system_clock::now(), 0, lib::orderType::NEW, m_symbol, lib::orderSide::ASK, 10, unscaled_price);

    json j = myOrder;

    f << j << std::endl;
}