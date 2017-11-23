#pragma once

#include <boost/operators.hpp>

#include <tuple>

namespace math
{
struct Position2f // : boost::additive<Position2f>,
                  //   boost::totally_ordered<Position2f>
{
    float x;
    float y;

    // Position2f(float _x, float _y) : x{_x}, y{_y}
    // {
    // }
};

inline bool operator==(const Position2f& lhs, const Position2f& rhs)
{
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}
// inline bool operator<(const Position2f& lhs, const Position2f& rhs);
inline Position2f operator+(const Position2f& lhs, const Position2f& rhs)
{
    return Position2f{lhs.x + rhs.x, lhs.y + rhs.y};
}
}
