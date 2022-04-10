#pragma once

#include"Event.hpp"
#include"orderBook.hpp"

class MatchingEngine: public Observable<MatchingEngine>
{
private:
    std::vector<std::unique_ptr<orderBook>> m_orderBooks;
    EventBlotter m_eventBlotter;

public:
    MatchingEngine() = default;
    explicit MatchingEngine(orderIdType maxOrderId);

    // Serve an incoming order by orderId and return a Boolean
    void serve(order& od);

    EventBlotter& get_eventBlotter();
};