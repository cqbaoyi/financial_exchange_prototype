#include<iostream>
#include<string>

#include"enum.hpp"
#include"MktDataPublisher.hpp"

void mktDataPublisher::event_occurred(MatchingEngine& matchingEngine)
{
    auto& eventBlotter = matchingEngine.get_eventBlotter();
    std::cout << "ask:" << "\n";
    for (auto& event: eventBlotter.m_ask_events)
    {
        std::cout << "price " << event.m_Price4 
                    << " quantity:  " << event.m_quantity 
                    << " action: " << event.m_action;
    }
    std::cout << "bid:" << "\n";
    for (auto& event: eventBlotter.m_bid_events)
    {
        std::cout << "price " << event.m_Price4 
                    << " quantity:  " << event.m_quantity 
                    << " action: " << event.m_action;
    }
}