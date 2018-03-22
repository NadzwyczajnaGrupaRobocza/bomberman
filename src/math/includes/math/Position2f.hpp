#pragma once

#include <boost/operators.hpp>

#include <tuple>

namespace math
{
struct Position2f : boost::additive<Position2f>,
                    boost::totally_ordered<Position2f>
{
    constexpr Position2f() : Position2f(.0f, .0f)
    {
    }

    constexpr Position2f(const float x_, const float y_) : x{x_}, y{y_}
    {
    }

    float x;
    float y;
};

namespace
{
auto tie(const Position2f& pos)
{
    return std::tie(pos.x, pos.y);
}
}

inline Position2f& operator+=(Position2f& lhs, const Position2f& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

inline bool operator==(const Position2f& lhs, const Position2f& rhs)
{
    return tie(lhs) == tie(rhs);
}

inline bool operator<(const Position2f& lhs, const Position2f& rhs)
{
    return tie(lhs) < tie(rhs);
}
}

inline std::ostream& operator<<(std::ostream& out,
                                const math::Position2f& position)
{
    return out << "Position2f{x:" << position.x << ", "
               << "y:" << position.y << "}\n";
}
