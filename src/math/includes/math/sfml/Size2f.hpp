#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2f.hpp"

namespace math
{
namespace sf
{
struct Size2f : public ::math::Size2f
{
    Size2f(const float width, const float height)
        : ::math::Size2f{width, height}
    {
    }

    Size2f(const ::math::Size2f& pos) : ::math::Size2f{pos}
    {
    }

    Size2f(const ::sf::Vector2f& pos) : ::math::Size2f{pos.x, pos.y}
    {
    }

    operator ::sf::Vector2f() const
    {
        return {width, height};
    }
};

inline bool operator==(const Size2f& lhs, const Size2f& rhs)
{
    return std::tie(lhs.width, lhs.height) == std::tie(rhs.width, rhs.height);
}
}
}
