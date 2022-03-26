#pragma once

#include<string>

class Price4
{
private:
    static constexpr uint8_t Scale4 = 4U;
    static constexpr int64_t PowScale4 = 10000LL;
    int64_t m_unscaled;

public:
    Price4() = default;

    explicit Price4(int64_t unscaled): m_unscaled(unscaled) {};

    // Convert from string
    explicit Price4(const std::string& s);

    // Convert to string
    std::string to_str() const;

    inline int64_t unscaled() const { return m_unscaled; };

    // Overloading operators
    inline bool operator==(const Price4& rhs) const;
    inline bool operator!=(const Price4& rhs) const;
    inline bool operator<(const Price4& rhs) const;
    inline bool operator>(const Price4& rhs) const;
    inline bool operator<=(const Price4& rhs) const;
    inline bool operator>=(const Price4& rhs) const; 

    // To be compatible with nlohmann::json::get_to, operator= is overloaded.
    void operator=(const std::string& s);
};

inline std::ostream& operator<<(std::ostream& os, const Price4& price4)
{
    return os << price4.to_str();
}
