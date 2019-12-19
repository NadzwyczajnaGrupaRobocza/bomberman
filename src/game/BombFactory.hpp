#pragma once

#include <memory>

#include "BombLauncher.hpp"
#include "math/Position2f.hpp"

class Bomb;

class BombFactory
{
public:
    virtual ~BombFactory() noexcept = default;

    [[nodiscard]] virtual auto
        create_time_bomb(math::Position2f, std::shared_ptr<BombLauncher>) const
        -> std::unique_ptr<Bomb> = 0;
};
