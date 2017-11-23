#pragma once

#include <memory>
#include "math/Position.hpp"
#include <boost/serialization/strong_typedef.hpp>
#include "Bomb.hpp"
#include <map>
#include <vector>
#include "GameWorld.hpp"

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


