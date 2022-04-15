#pragma once

#include<array>
#include<iostream>
#include<string>

namespace lib
{
    enum class orderType: uint32_t {
        NA = 0,
        NEW = 1,
        CANCEL = 2,
    };

    constexpr uint32_t N_orderSide = 3;
    enum class orderSide: uint32_t {
        NA = 0,
        BID = 1,
        ASK = 2,
    };
    static std::array<std::string, N_orderSide> orderSideStr = {"NA", "BID", "ASK"};

    constexpr uint32_t N_symbol = 6;
    enum class symbol: uint32_t {
        NA = 0,
        AAPL = 1,
        MSFT = 2,
        NVDA = 3,
        AVGO = 4,
        CSCO = 5,
    };
    static std::array<std::string, N_symbol> symbolStr = {"NA", "AAPL", "MSFT", "NVDA", "AVGO", "CSCO"};

    constexpr uint32_t N_event = 3;
    enum class event: uint32_t {
        NA = 0,
        TRADE = 1,
        DEPTH_UPDATE = 2,
    };
    static std::array<std::string, N_event> eventStr = {"NA", "TRADE", "DEPTH_UPDATE"};

    constexpr uint32_t N_action = 4;
    enum class action: uint32_t {
        NA = 0,
        ADD = 1,
        MODIFY = 2,
        DELETE = 3,
    };
    static std::array<std::string, N_action> actionStr = {"NA", "ADD", "MODIFY", "DELETE"};
}

inline std::ostream& operator<<(std::ostream& os, lib::orderType & orderType)
{
    switch(orderType)
    { 
        case lib::orderType::NA: return os << "NA";
        case lib::orderType::NEW: return os << "NEW";
        case lib::orderType::CANCEL: return os << "CANCEL";
    }
}

inline std::ostream& operator<<(std::ostream& os, lib::orderSide & orderSide)
{
    switch(orderSide)
    {
        case lib::orderSide::NA: return os << "NA";
        case lib::orderSide::ASK: return os << "ASK";
        case lib::orderSide::BID: return os << "BID";
    }
}

inline std::ostream& operator<<(std::ostream& os, lib::symbol & symbol)
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

inline std::ostream& operator<<(std::ostream& os, lib::action& action)
{
    switch(action)
    {
        case lib::action::NA: return os << "NA";
        case lib::action::ADD: return os << "ADD";
        case lib::action::MODIFY: return os << "MODIFY";
        case lib::action::DELETE: return os << "DELETE";
    }
}