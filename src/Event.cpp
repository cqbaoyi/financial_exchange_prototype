#include"Event.hpp"


void to_json(json& j, const Event& event)
{
    j = json{
        {"action", lib::actionStr[static_cast<int32_t>(event.m_action)]},
        {"price", event.m_price.to_str()},
        {"quantity", event.m_quantity},
        {"side", lib::orderSideStr[static_cast<int32_t>(event.m_orderSide)]},
    };
}


void EventBlotter::addEvent(Event&& event)
{
    m_events.emplace_back(std::move(event));
}