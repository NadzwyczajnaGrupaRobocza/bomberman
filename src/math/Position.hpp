#pragma once
#include <tuple>

namespace math
{
struct Position2
{
    float x;
    float y;
};

inline bool operator==(const Position2& a, const Position2& b)
{
    return std::tie(a.x, a.y) == std::tie(b.x, b.y);
}

inline bool operator<(const Position2& a, const Position2& b)
{
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

}
