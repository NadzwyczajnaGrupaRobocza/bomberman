#pragma once

#include "math/Position2f.hpp"

class BombLauncher
{
public:
    virtual ~BombLauncher() noexcept = default;

    virtual bool try_spawn_bomb(const math::Position2f) = 0;
    virtual void notify_exploded() = 0;
};
