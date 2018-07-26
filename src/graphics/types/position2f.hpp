#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Position2f.hpp"

namespace graphics
{
struct position2f : public ::math::Position2f
{
    position2f(float x_, float y_) : ::math::Position2f(x_, y_)
    {
    }

    position2f(const ::math::Position2f& pos) : position2f(pos.x, pos.y)
    {
    }

    position2f(const ::sf::Vector2f& pos) : position2f(pos.x, pos.y)
    {
    }

    operator ::sf::Vector2f() const
    {
        return {x, y};
    }
};
}
