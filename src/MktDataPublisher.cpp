#include<iostream>
#include<string>

#include"enum.hpp"
#include"MktDataPublisher.hpp"

void mktDataPublisher::publish(MatchingEngine& matchingEngine)
{
    EventBlotter& eventBlotter = matchingEngine.get_eventBlotter();
    
    for (auto& event: eventBlotter.m_events)
        std::cout << json(event) << "\n";

    // TODO: output price level event data
}