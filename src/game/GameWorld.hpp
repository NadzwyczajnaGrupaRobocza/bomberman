#pragma once

#include <memory>

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

    [[nodiscard]] virtual auto is_bomb_at_pos(const BombPosition&) const -> bool = 0;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) = 0;
    virtual void register_explosion(ExplosionPosition,
                                    std::unique_ptr<Explosion>) = 0;

    virtual void update(DeltaTime) = 0;
};
