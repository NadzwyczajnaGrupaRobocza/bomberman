#pragma once

#include <utility>
using Vector2D = std::tuple<float, float>;

class HumanPlayer
{
    virtual ~HumanPlayer() = default;

    virtual Vector2D get_direction() = 0;
    virtual bool wants_bomb() = 0;
};
