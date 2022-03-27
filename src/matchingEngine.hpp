#pragma once

#include"orderBook.hpp"

class matchingEngine
{
private:
    std::unique_ptr<orderBook> m_ob;
public:
    matchingEngine() = default;
    matchingEngine(orderBook& ob);
    
};