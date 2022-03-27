#pragma once

#include<chrono>
#include<nlohmann/json.hpp>

#include"enum.hpp"
#include"Price4.hpp"

using json = nlohmann::ordered_json;

typedef std::chrono::seconds Seconds;
typedef std::chrono::system_clock Clock;
typedef uint64_t orderIdType;

class order
{
private:
    std::chrono::time_point<Clock> m_timeStamp;
    orderIdType m_orderId;
    lib::orderType m_orderType;
    lib::symbol m_symbol; 
    lib::orderSide m_orderSide;
    int64_t m_quantity;
    Price4 m_limitPrice;

public:
    order() = default;
    order(const std::chrono::time_point<Clock>& timeStamp,
        orderIdType orderId, 
        const lib::orderType& oT, 
        const lib::symbol& symbol = lib::symbol::NA, 
        const lib::orderSide& os = lib::orderSide::NA, 
        int64_t quantity = 0, 
        int64_t limitPrice = 0): 
        m_timeStamp(timeStamp),
        m_orderId(orderId++), 
        m_orderType(oT),
        m_symbol(symbol),
        m_orderSide(os),
        m_quantity(quantity),
        m_limitPrice(limitPrice)
        {};

    // Getters
    inline std::chrono::time_point<Clock> get_time() const { return m_timeStamp; };

    inline orderIdType get_orderId() const { return m_orderId; };

    inline lib::orderType get_orderType() const { return m_orderType; };

    inline lib::symbol get_symbol() const { return m_symbol; };

    inline lib::orderSide get_orderSide() const { return m_orderSide; };

    inline int64_t get_quantity() const { return m_quantity; };

    inline Price4 get_Price4() const { return m_limitPrice; };

    // Setters
    inline std::chrono::time_point<std::chrono::system_clock>& set_time() { return m_timeStamp; };

    inline orderIdType& set_orderId() { return m_orderId; };

    inline lib::orderType& set_orderType() { return m_orderType; };

    inline lib::symbol& set_symbol() { return m_symbol; };

    inline lib::orderSide& set_orderSide() { return m_orderSide; };

    inline int64_t& set_quantity() { return m_quantity; };

    inline Price4& set_Price4() { return m_limitPrice; };

    // Print out order info
    void print_info();
};

// Conversion to/from json
void to_json(json& j, const order& od);
void from_json(const json& j, order& od);