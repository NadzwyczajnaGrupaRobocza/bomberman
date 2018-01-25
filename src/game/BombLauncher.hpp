#pragma once

#include "math/Position.hpp"

class BombLauncher
{
public:
    virtual ~BombLauncher() noexcept = default;

    virtual bool try_spawn_bomb(const math::Position2) = 0;
    virtual void notifyExploded() = 0;
};
