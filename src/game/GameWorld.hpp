#pragma once

#include <memory>
#include "math/Position.hpp"
#include <boost/serialization/strong_typedef.hpp>
#include "Bomb.hpp"
#include <map>
#include <vector>
#include "BombPosition.hpp"
#include "ElapsedTime.hpp"
#include "ExplosionPosition.hpp"

using Explosion = std::size_t;

class GameWorld
{
public:

    virtual bool is_bomb_at_pos(const BombPosition&) const = 0;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) = 0;
    virtual void register_explosion(ExplosionPosition, std::unique_ptr<Explosion>) = 0;

    virtual void update(ElapsedTime) = 0;
    virtual ~GameWorld() = default;
};

class BombermanGameWorld : public GameWorld
{
public:
    virtual bool is_bomb_at_pos(const BombPosition&) const override;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) override;
    virtual void register_explosion(ExplosionPosition, std::unique_ptr<Explosion>) override;

    virtual void update(ElapsedTime) override;

private:
    std::vector<std::unique_ptr<Entity>> entity;
    std::map<BombPosition, std::unique_ptr<Bomb>> bombs;
    std::map<ExplosionPosition, std::unique_ptr<Explosion>> explosions;
};



