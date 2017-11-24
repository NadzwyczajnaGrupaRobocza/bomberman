#pragma once

#include <boost/operators.hpp>

#include <tuple>

namespace math
{
struct Position2f : boost::additive<Position2f>,
                    boost::totally_ordered<Position2f>
{
    constexpr Position2f(const float x_, const float y_) : x{x_}, y{y_}
    {
    }

    float x;
    float y;
};

inline Position2f& operator+=(Position2f& lhs, const Position2f& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

inline bool operator==(const Position2f& lhs, const Position2f& rhs)
{
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

inline bool operator<(const Position2f& lhs, const Position2f& rhs)
{
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}
}
