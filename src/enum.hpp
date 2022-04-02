#pragma once

#include<array>
#include<string>

namespace lib
{
    enum class orderType {
        NA = 0,
        NEW = 1,
        CANCEL = 2,
    };

    constexpr uint32_t N_orderSide = 3;
    enum class orderSide {
        NA = 0,
        BID = 1,
        ASK = 2,
    };
    static std::array<std::string, N_orderSide> orderSideStr = {"NA", "BID", "ASK"};

    constexpr uint32_t N_symbol = 6;
    enum class symbol {
        NA = 0,
        AAPL = 1,
        MSFT = 2,
        NVDA = 3,
        AVGO = 4,
        CSCO = 5,
    };
    static std::array<std::string, N_symbol> symbolStr = {"NA", "AAPL", "MSFT", "NVDA", "AVGO", "CSCO"};
}

inline std::ostream& operator<<(std::ostream & os, lib::orderType & orderType)
{
    switch(orderType)
    { 
        case lib::orderType::NA: return os << "NA";
        case lib::orderType::NEW: return os << "NEW";
        case lib::orderType::CANCEL: return os << "CANCEL";
    }
}

inline std::ostream& operator<<(std::ostream & os, lib::orderSide & orderSide)
{
    switch(orderSide)
    {
        case lib::orderSide::NA: return os << "NA";
        case lib::orderSide::ASK: return os << "ASK";
        case lib::orderSide::BID: return os << "BID";
    }
}

inline std::ostream& operator<<(std::ostream & os, lib::symbol & symbol)
{
    switch(symbol)
    {
        case lib::symbol::NA: return os << "NA";
        case lib::symbol::AAPL: return os << "AAPL";
        case lib::symbol::MSFT: return os << "MSFT";
        case lib::symbol::NVDA: return os << "NVDA";
        case lib::symbol::AVGO: return os << "AVGO";
        case lib::symbol::CSCO: return os << "CSCO";
    }
}