#include<iostream>

#include"orderBook.hpp"
#include"orderGenerator.hpp"
#include"orderReader.hpp"

int main()
{
    std::cout << "Market opens" << std::endl;

    lib::symbol symbol = lib::symbol::MSFT;

    orderGenerator myOrderGenerator(symbol);
    myOrderGenerator.run();

    orderReader myOrderReader(symbol);
    myOrderReader.run();

    std::cout << "Market closes" << std::endl;

    return 0;
}