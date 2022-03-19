#include<iomanip>
#include"orderGenerator.hpp"


Price4::Price4(const std::string& s)
{
    try
    {
        if (s.empty())
            throw std::invalid_argument("Invalid price: empty");
        uint32_t n = s.size(), idx_dot = n;
        for (uint32_t i = 0; i < n; ++i)
        {
            if (s[i] == '.')
            {
                if (i == 0U)
                    throw std::invalid_argument("Invalid price: the integer part of a price cannot be empty");
                if (idx_dot < n)
                    throw std::invalid_argument("Invalid price: more than one decimal point found");
                idx_dot = i;
            }
            else if (!isdigit(s[i]))
                throw std::invalid_argument("Invalid price: non-digit character found"); 
        }

        m_unscaled = std::stoll(s.substr(0, idx_dot)) * PowScale4;
        uint32_t n_decimal_digits = n - idx_dot ;
        if (n_decimal_digits)
            m_unscaled += std::stoll(s.substr(idx_dot + 1U, n - idx_dot - 1U)) * std::pow(10LL, 5U - n + idx_dot);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string Price4::to_str() const
{
    std::string res = "";
    try
    {
        int64_t integer = m_unscaled / PowScale4;
        int64_t decimal = m_unscaled % PowScale4;
        std::string s_decimal = std::to_string(decimal);
        res = std::to_string(integer) + "." + std::string(Scale4 - s_decimal.size(), '0') + s_decimal;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return res;
}

inline bool Price4::operator<(const Price4& rhs) const
{
    return m_unscaled < rhs.m_unscaled;
}

inline bool Price4::operator>(const Price4& rhs) const
{
    return rhs < *this;
}

inline bool Price4::operator<=(const Price4& rhs) const
{
    return !(*this > rhs);
}

inline bool Price4::operator>=(const Price4& rhs) const
{
    return !(*this < rhs);
}

uint64_t order::globalOrderId = 0;

orderGenerator::orderGenerator(std::chrono::time_point<std::chrono::system_clock> timeStamp): m_timeStamp(timeStamp)
{
    mt = std::mt19937(rd());
    dist = std::uniform_int_distribution<int64_t>(0, 10000);
}

void orderGenerator::run()
{
    std::fstream f("orderInputs.dat", std::ios::out);

    std::chrono::time_point<std::chrono::system_clock> t_start = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> t_end = t_start + std::chrono::hours(6) + std::chrono::minutes(30);

    const std::time_t t_s = std::chrono::system_clock::to_time_t(t_start);
    const std::time_t t_e = std::chrono::system_clock::to_time_t(t_end);
    std::cout << std::put_time(std::localtime(&t_s), "%F %T.") << std::endl;
    std::cout << std::put_time(std::localtime(&t_e), "%F %T.") << std::endl;
    std::cout << dist(mt) << std::endl;
}