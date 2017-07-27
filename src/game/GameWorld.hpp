#pragma once

#include <memory>
#include "math/Position.hpp"
#include <boost/serialization/strong_typedef.hpp>

class GameWorld
{
public:
    BOOST_STRONG_TYPEDEF(math::Position2, BombPosition)
    BOOST_STRONG_TYPEDEF(math::Position2, ExplosionPosition)
    BOOST_STRONG_TYPEDEF(std::size_t, TimeToExplode)

    using Explosion = std::size_t;

    bool is_bomb_at_pos(BombPosition) const = 0;
    std::unique_ptr<Bomb> create_bomb(BombPosition, TimeToExplode) const = 0;
    std::unique_ptr<Explosion> create_explosion(ExplosionPosition) const = 0;
};

class BombermanGameWorld : public GameWorld
{
public:


};



