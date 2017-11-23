#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Position2f.hpp"

namespace math
{
namespace sf
{
struct Position2f : public ::math::Position2f
{
    Position2f(float x, float y) : ::math::Position2f{x, y}
    {
    }

    Position2f(const ::math::Position2f& pos) : ::math::Position2f{pos}
    {
    }

    Position2f(const ::sf::Vector2f& pos) : ::math::Position2f{pos.x, pos.y}
    {
    }

    operator ::sf::Vector2f() const
    {
        return {x, y};
    }
};
}
}
