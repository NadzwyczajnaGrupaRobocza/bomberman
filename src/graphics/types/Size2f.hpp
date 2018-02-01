#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2f.hpp"

namespace graphics
{
struct Size2f : ::math::Size2f
{
    Size2f(const float width_, const float height_)
        : ::math::Size2f{width_, height_}
    {
    }

    Size2f(const ::math::Size2f& size) : Size2f{size.width, size.height}
    {
    }

    Size2f(const ::sf::Vector2f& size) : Size2f{size.x, size.y}
    {
    }

    operator ::sf::Vector2f() const
    {
        return {width, height};
    }
};
}
