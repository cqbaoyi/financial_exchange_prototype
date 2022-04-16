#pragma once

#include"enum.hpp"
#include"order.hpp"
#include"Price4.hpp"

// An Event object should have the finest level of information, which might be an overkill right now.
// How to process all the events is the Observers' responsibility.
class Event
{
public:
    lib::action m_action;
    Price4 m_price;
    orderQuantityType m_quantity;
    lib::orderSide m_orderSide;

    explicit Event(lib::action action,
                   Price4 price,
                   orderQuantityType quantity,
                   lib::orderSide orderSide):
                   m_action(action),
                   m_price(price),
                   m_quantity(quantity),
                   m_orderSide(orderSide)
    {}
};

// Conversion to json
void to_json(json& j, const Event& event);

class EventBlotter
{
public:
    // One price level has one total quantity.
    std::vector<Event> m_events;
    
    EventBlotter() = default;

    void addEvent(Event&& event);

    inline void clear()
    {
        m_events.clear();
    }
};