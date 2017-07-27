#pragma once

#include <memory>
#include "math/Position.hpp"
#include <boost/serialization/strong_typedef.hpp>
#include "Bomb.hpp"

class GameWorld
{
public:
    BOOST_STRONG_TYPEDEF(math::Position2, BombPosition)
    BOOST_STRONG_TYPEDEF(math::Position2, ExplosionPosition)
    BOOST_STRONG_TYPEDEF(std::size_t, TimeToExplode)

    using Explosion = std::size_t;

    virtual bool is_bomb_at_pos(const BombPosition&) const = 0;
    virtual std::unique_ptr<Bomb> create_bomb(const BombPosition&, const TimeToExplode) const = 0;
    virtual std::unique_ptr<Explosion> create_explosion(const ExplosionPosition&) const = 0;

    virtual ~GameWorld() = default;
};

class BombermanGameWorld : public GameWorld
{
public:


};



