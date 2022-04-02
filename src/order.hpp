#pragma once

#include<chrono>
#include<nlohmann/json.hpp>

#include"enum.hpp"
#include"Price4.hpp"

using json = nlohmann::ordered_json;

typedef std::chrono::seconds Seconds;
typedef std::chrono::system_clock Clock;
typedef uint64_t orderIdType;
typedef int64_t orderQuantityType;

class order
{
private:
    std::chrono::time_point<Clock> m_timeStamp;
    orderIdType m_orderId;
    lib::orderType m_orderType;
    lib::symbol m_symbol; 
    lib::orderSide m_orderSide;
    orderQuantityType m_quantity;
    Price4 m_limitPrice;

    friend void from_json(const json& j, order& od);

public:
    order() = default;
    explicit order(const std::chrono::time_point<Clock>& timeStamp,
        orderIdType orderId, 
        const lib::orderType& oT, 
        const lib::symbol& symbol = lib::symbol::NA, 
        const lib::orderSide& os = lib::orderSide::NA, 
        orderQuantityType quantity = 0, 
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
    inline std::chrono::time_point<Clock> get_time() const { return m_timeStamp; }
    inline orderIdType get_orderId() const { return m_orderId; }
    inline lib::orderType get_orderType() const { return m_orderType; }
    inline lib::symbol get_symbol() const { return m_symbol; }
    inline lib::orderSide get_orderSide() const { return m_orderSide; }
    inline orderQuantityType get_quantity() const { return m_quantity; }
    inline Price4 get_Price4() const { return m_limitPrice; }

    // Setters
    inline void set_time(std::chrono::time_point<std::chrono::system_clock>& t) { m_timeStamp = t; }
    inline void set_orderId(orderIdType orderId) { m_orderId = orderId; }
    inline void set_orderType(lib::orderType orderType) { m_orderType = orderType; }
    inline void set_symbol(lib::symbol symbol) { m_symbol = symbol; }
    inline void set_orderSide(lib::orderSide orderSide) { m_orderSide = orderSide; }
    inline void set_quantity(orderQuantityType quantity) { m_quantity = quantity; }
    inline void set_Price4(Price4& limitPrice) { m_limitPrice = limitPrice; }

    // Print out order info
    void print_info();
};

// Conversion to/from json
void to_json(json& j, const order& od);
void from_json(const json& j, order& od);