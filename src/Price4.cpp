#include<cmath>
#include<iomanip>
#include<iostream>

#include"Price4.hpp"

/*********************************

Price4 implementation

*********************************/

Price4::Price4(const std::string& s)
{
    *this = s;
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

void Price4::operator=(const std::string& s)
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