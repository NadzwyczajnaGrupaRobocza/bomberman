#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Size2u.hpp"

namespace graphics
{
struct window_size : ::math::Size2u, boost::totally_ordered<window_size>
{
    window_size(const unsigned width_, const unsigned height_)
        : ::math::Size2u{width_, height_}
    {
    }

    window_size(const ::math::Size2u& size)
        : window_size{size.width, size.height}
    {
    }

    window_size(const ::sf::Vector2u& size) : window_size{size.x, size.y}
    {
    }

    operator ::sf::Vector2u() const
    {
        return {width, height};
    }
};

}
