#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2u.hpp"

namespace graphics
{
struct WindowSize : ::math::Size2u, boost::totally_ordered<WindowSize>
{
    WindowSize(const unsigned width_, const unsigned height_)
        : ::math::Size2u{width_, height_}
    {
    }

    WindowSize(const ::math::Size2u& size) : WindowSize{size.width, size.height}
    {
    }

    WindowSize(const ::sf::Vector2u& size) : WindowSize{size.x, size.y}
    {
    }

    operator ::sf::Vector2u() const
    {
        return {width, height};
    }
};

inline bool operator==(const WindowSize& lhs, const ::sf::Vector2u& rhs)
{
    return sf::Vector2u(lhs) == rhs;
}
}
