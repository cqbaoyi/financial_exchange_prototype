#include<iostream>
#include"orderBook.hpp"
#include"orderGenerator.hpp"

int main()
{
    std::cout << "Market opens" << std::endl;

    Price4 p0(10L);
    order od0(std::chrono::system_clock::now(), orderType::NEW, ticker::AAPL, orderSide::ASK, 100, p0);

    orderBook ob;

    std::chrono::time_point<std::chrono::system_clock> current = std::chrono::system_clock::now();
    orderGenerator og(current);
    og.run();

    std::cout << "Market closes" << std::endl;

    return 0;
}