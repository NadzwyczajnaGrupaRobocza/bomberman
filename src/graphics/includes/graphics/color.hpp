#pragma once

#include <boost/operators.hpp>

namespace graphics
{
struct color // : boost::equality_comparable<color>
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

inline bool operator==(const color& lhs, const color& rhs)
{
    const auto tie = [](const color& c) { return std::tie(c.r, c.g, c.b); };
    return tie(lhs) == tie(rhs);
}

inline bool operator!=(const color& lhs, const color& rhs)
{
    return !(lhs == rhs);
}
} // namespace graphics
