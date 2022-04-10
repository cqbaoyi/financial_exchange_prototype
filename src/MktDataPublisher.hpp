#pragma once

#include"MatchingEngine.hpp"
#include"Observer.hpp"

// Price level market data publisher
class mktDataPublisher: public Observer<MatchingEngine>
{
private:
    void event_occurred(MatchingEngine& matchingEngine) override;

public:
    mktDataPublisher() = default;
};