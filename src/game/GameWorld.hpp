#pragma once

#include "BombPosition.hpp"
#include "DeltaTime.hpp"
#include "ExplosionPosition.hpp"
#include "graphics/window_size.hpp"

class Bomb;

using Explosion = std::size_t; // temporary, remove and destroy when Exp added

class GameWorld
{
public:
    virtual ~GameWorld() = default;

    virtual bool is_bomb_at_pos(const BombPosition&) const = 0;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) = 0;
    virtual void register_explosion(ExplosionPosition,
                                    std::unique_ptr<Explosion>) = 0;

    virtual void update(DeltaTime) = 0;
};
