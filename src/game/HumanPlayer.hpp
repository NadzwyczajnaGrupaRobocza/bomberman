#pragma once

#include <utility>
#include <glm/glm.hpp>

using VectorInt2D = glm::i8vec2;

class HumanPlayer
{
public:
    virtual ~HumanPlayer() = default;

    virtual VectorInt2D get_direction() const = 0;
    virtual bool wants_bomb() const = 0;
};
