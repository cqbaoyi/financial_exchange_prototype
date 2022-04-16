#include<iostream>

#include"orderGenerator.hpp"
#include"orderReader.hpp"
#include"MktDataPublisher.hpp"
#include"MatchingEngine.hpp"

int main()
{
    lib::symbol symbol = lib::symbol::MSFT;

    //orderGenerator myOrderGenerator(symbol);
    //myOrderGenerator.run();

    constexpr orderIdType maxOrderId = 1'000'000;
    std::shared_ptr<orderPool> op(std::make_shared<orderPool>(maxOrderId));

    mktDataPublisher publisher;
    MatchingEngine engine(op);
    engine.subscribe(publisher);

    orderReader myOrderReader(symbol);
    myOrderReader.run(engine);

    //order order0(Clock::now(), 0, lib::orderType::NEW, symbol, lib::orderSide::BID, 100, 150);
    //order order1(Clock::now(), 1, lib::orderType::NEW, symbol, lib::orderSide::BID, 100, 200);
    //order order2(Clock::now(), 2, lib::orderType::NEW, symbol, lib::orderSide::ASK, 100, 300);
    //engine.serve(order0);
    //engine.serve(order1);
    //engine.serve(order2);

    //engine.unsubscribe(publisher);

    return 0;
}