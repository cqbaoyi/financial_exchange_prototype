#include<fstream>
#include<iostream>
#include<nlohmann/json.hpp>

#include"order.hpp"
#include"orderReader.hpp"

orderReader::orderReader(lib::symbol symbol): m_symbol(symbol)
{
    m_fileName = "orders_" + lib::symbolStr[static_cast<uint32_t>(symbol)] + ".json";
}

void orderReader::run(MatchingEngine& matchingEngine)
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
            matchingEngine.serve(od);
            //od.print_info();
        }
        catch (json::parse_error& ex)
        {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
    }
}