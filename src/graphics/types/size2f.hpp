#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2f.hpp"

namespace graphics
{
struct size2f : ::math::Size2f
{
    size2f(const float width_, const float height_)
        : ::math::Size2f{width_, height_}
    {
    }

    size2f(const ::math::Size2f& size) : size2f{size.width, size.height}
    {
    }

    size2f(const ::sf::Vector2f& size) : size2f{size.x, size.y}
    {
    }

    operator ::sf::Vector2f() const
    {
        return {width, height};
    }
};
}
