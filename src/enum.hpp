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