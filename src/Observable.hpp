#pragma once

#include<vector>

#include"Observer.hpp"

template<typename T>
class Observable
{
private:
    // TODO: replace raw pointer
    std::vector<Observer<T>*> observers;

public:
    void notify(T& source)
    {
        for (auto& observer: observers)
            observer->event_occurred(source);
    }

    void subscribe(Observer<T>& observer)
    {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
    }
};