#include<fstream>
#include<iostream>
#include<nlohmann/json.hpp>

#include"order.hpp"
#include"orderReader.hpp"

using json = nlohmann::json;

orderReader::orderReader(const std::string& fileName): m_fileName(fileName)
{   
}

void orderReader::run()
{
    std::fstream f(m_fileName, std::ios::in);

    std::string line;
    order od;
    json j;
    // https://json.nlohmann.me/features/parsing/json_lines/
    // Using operator>> leads to an exception at the end of the file. Use getline instead.
    while(std::getline(f, line))
    {
        try
        {
            j = json::parse(line);
            od = j;
            od.print_info();
        }
        catch (json::parse_error& ex)
        {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
    }
}