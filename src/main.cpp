#include<iostream>
#include"orderBook.hpp"

int main()
{
    std::cout << "Market opens" << std::endl;

    //orderBook ob;

    orderGenerator og;
    og.run();

    std::cout << "Market closes" << std::endl;

    return 0;
}