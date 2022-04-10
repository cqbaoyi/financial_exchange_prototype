#pragma once

#include"enum.hpp"
#include"order.hpp"
#include"Price4.hpp"

// Price level event
class Event
{
public:
    Price4 m_Price4;
    orderQuantityType m_quantity;
    lib::action m_action;

    explicit Event(Price4 p, 
        orderQuantityType q, 
        lib::action a): 
        m_Price4(p), 
        m_quantity(q), 
        m_action(a)
    {}
};

struct EventBlotter
{
public:
    std::vector<Event> m_bid_events, m_ask_events;

    inline void clear() 
    {
        m_bid_events.clear();
        m_ask_events.clear();
    }
};