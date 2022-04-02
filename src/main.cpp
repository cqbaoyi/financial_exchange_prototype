#include<iostream>

#include"orderGenerator.hpp"
#include"orderReader.hpp"
#include"matchingEngine.hpp"

int main()
{
    lib::symbol symbol = lib::symbol::MSFT;

    orderGenerator myOrderGenerator(symbol);
    myOrderGenerator.run();

    //orderReader myOrderReader(symbol);
    //myOrderReader.run();

    order myOrder(Clock::now(), 0, lib::orderType::NEW, lib::symbol::MSFT, lib::orderSide::ASK, 100, 150);

    constexpr orderIdType maxOrderId = 1'000'000;

    matchingEngine engine(maxOrderId);
    engine.serve(myOrder);

    return 0;
}