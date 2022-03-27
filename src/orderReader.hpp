#pragma once

#include<string>

class orderReader
{
private:
    lib::symbol m_symbol;
    std::string m_fileName;
public:
    orderReader() = default;
    orderReader(lib::symbol symbol);
    void run();
};