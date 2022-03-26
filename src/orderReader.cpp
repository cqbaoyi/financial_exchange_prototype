#include<fstream>
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

    json j;
    f >> j;

    order od = j;
    od.print_info();
}