#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2u.hpp"

namespace math
{
namespace sf
{
struct Size2u : public ::math::Size2u
{
    Size2u(const unsigned width, const unsigned height)
        : ::math::Size2u{width, height}
    {
    }

    Size2u(const ::math::Size2u& pos) : ::math::Size2u{pos}
    {
    }

    Size2u(const ::sf::Vector2u& pos) : ::math::Size2u{pos.x, pos.y}
    {
    }

    operator ::sf::Vector2u() const
    {
        return {width, height};
    }
};

inline bool operator==(const Size2u& lhs, const Size2u& rhs)
{
    return std::tie(lhs.width, lhs.height) == std::tie(rhs.width, rhs.height);
}
}
}
