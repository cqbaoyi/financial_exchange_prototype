#pragma once

#include"Event.hpp"
#include"orderBook.hpp"

class MatchingEngine: public Observable<MatchingEngine>
{
private:
    std::vector<std::unique_ptr<orderBook>> m_orderBooks;
    std::shared_ptr<orderPool> m_orderPool;
    EventBlotter m_eventBlotter;

public:
    MatchingEngine() = default;
    explicit MatchingEngine(std::shared_ptr<orderPool> op);

    // Serve an incoming order by orderId and return a Boolean
    void serve(order& od);

    EventBlotter& get_eventBlotter();
};