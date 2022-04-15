#pragma once

template<typename T>
class Observer
{
public:
    virtual void publish(T& source) = 0;
};
