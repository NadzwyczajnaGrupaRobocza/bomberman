#pragma once

#include <memory>

#include "math/Position2f.hpp"

class Bomb;

class BombFactory
{
public:
    virtual ~BombFactory() noexcept = default;

    virtual std::unique_ptr<Bomb> create_time_bomb(math::Position2f) const = 0;
};
