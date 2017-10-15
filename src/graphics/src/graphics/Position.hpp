#pragma once

namespace graphics
{
struct Position
{
    float x, y;
};

inline Position operator+(const Position& lhs, const Position& rhs)
{
    return Position{lhs.x + rhs.x, lhs.y + rhs.y};
}
}
