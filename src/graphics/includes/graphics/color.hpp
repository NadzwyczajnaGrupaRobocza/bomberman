#pragma once

#include <tuple>

namespace graphics
{
struct color
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

namespace colors
{
constexpr color white = color{255, 255, 255};
constexpr color red = color{255, 0, 0};
constexpr color green = color{0, 255, 0};
constexpr color blue = color{0, 0, 255};
constexpr color cyan = color{0, 255, 255};
constexpr color magenta = color{255, 0, 255};
constexpr color yellow = color{255, 255, 0};
constexpr color black = color{0, 0, 0};
}

}
