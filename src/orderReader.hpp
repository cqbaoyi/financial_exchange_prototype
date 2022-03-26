#pragma once

#include<string>

class orderReader
{
private:
    std::string m_fileName;
public:
    orderReader() = default;
    orderReader(const std::string& fileName);
    void run();
};