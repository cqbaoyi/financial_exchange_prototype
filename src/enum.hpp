#pragma once

namespace lib
{
    enum class orderType {
        NEW = 0,
        CANCEL = 1,
    };

    enum class orderSide {
        BID = 0,
        ASK = 1,
    };

    enum class symbol {
        AAPL = 0,
        MSFT = 1,
        NVDA = 2,
        AVGO = 3,
        CSCO = 4,
    };
}

inline std::ostream& operator<<(std::ostream & os, lib::orderType & orderType)
{
    switch(orderType)
    {
        case lib::orderType::NEW: return os << "NEW";
        case lib::orderType::CANCEL: return os << "CANCEL";
    }
}

inline std::ostream& operator<<(std::ostream & os, lib::orderSide & orderSide)
{
    switch(orderSide)
    {
        case lib::orderSide::ASK: return os << "ASK";
        case lib::orderSide::BID: return os << "BID";
    }
}

inline std::ostream& operator<<(std::ostream & os, lib::symbol & symbol)
{
    switch(symbol)
    {
        case lib::symbol::AAPL: return os << "AAPL";
        case lib::symbol::MSFT: return os << "MSFT";
        case lib::symbol::NVDA: return os << "NVDA";
        case lib::symbol::AVGO: return os << "AVGO";
        case lib::symbol::CSCO: return os << "CSCO";
    }
}