#include"orderGenerator.hpp"

orderGenerator::orderGenerator(std::chrono::time_point<std::chrono::system_clock> timeStamp): m_timeStamp(timeStamp)
{
    mt = std::mt19937(rd());
    dist = std::uniform_int_distribution<int64_t>(0, 1000);
}

void orderGenerator::run()
{
    std::cout << dist(mt) << std::endl;
}