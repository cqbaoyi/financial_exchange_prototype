#include<iostream>
#include"orderBook.hpp"
#include"orderGenerator.hpp"
#include"orderReader.hpp"

int main()
{
    std::cout << "Market opens" << std::endl;

    std::string fileName = "orderInputs.json";

    orderGenerator myOrderGenerator(fileName);
    myOrderGenerator.run();

    orderReader myOrderReader(fileName);
    myOrderReader.run();

    std::cout << "Market closes" << std::endl;

    return 0;
}