#pragma once

#include"MatchingEngine.hpp"
#include"Observer.hpp"

// Price level market data publisher
class mktDataPublisher: public Observer<MatchingEngine>
{
private:
    void publish(MatchingEngine& matchingEngine) override;

public:
    mktDataPublisher() = default;
};