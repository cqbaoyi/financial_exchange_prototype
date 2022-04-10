#pragma once

template<typename T>
class Observer
{
public:
    virtual void event_occurred(T& source) = 0;
};
