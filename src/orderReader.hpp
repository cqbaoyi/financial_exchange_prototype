#pragma once

#include<string>

#include"MatchingEngine.hpp"

class orderReader
{
private:
    lib::symbol m_symbol;
    std::string m_fileName;
public:
    orderReader() = default;
    orderReader(lib::symbol symbol);
    void run(MatchingEngine& matchingEngine);
};