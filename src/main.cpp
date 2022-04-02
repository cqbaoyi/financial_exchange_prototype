#include<iostream>

#include"orderBook.hpp"
#include"orderGenerator.hpp"
#include"orderReader.hpp"

int main()
{
    lib::symbol symbol = lib::symbol::MSFT;

    orderGenerator myOrderGenerator(symbol);
    myOrderGenerator.run();

    orderReader myOrderReader(symbol);
    myOrderReader.run();

    return 0;
}