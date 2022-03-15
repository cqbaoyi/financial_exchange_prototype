#pragma once

#include<chrono>
#include<iostream>
#include<random>
#include"enum.hpp"

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