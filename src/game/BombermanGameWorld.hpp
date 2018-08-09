#pragma once

#include <memory>
#include <boost/serialization/strong_typedef.hpp>
#include "Bomb.hpp"
#include <map>
#include <vector>
#include "GameWorld.hpp"
#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"

#include "SimpleMap.hpp"

class BombermanGameWorld : public GameWorld
{
public:
    BombermanGameWorld(std::unique_ptr<physics::PhysicsEngine>,
                       std::unique_ptr<graphics::RendererPool>);

    virtual bool is_bomb_at_pos(const BombPosition&) const override;

    virtual void register_bomb(BombPosition, std::unique_ptr<Bomb>) override;
    virtual void register_explosion(ExplosionPosition, std::unique_ptr<Explosion>) override;

    virtual void update(DeltaTime) override;

private:

    std::vector<std::unique_ptr<Entity>> entity;
    std::map<BombPosition, std::unique_ptr<Bomb>> bombs;
    std::map<ExplosionPosition, std::unique_ptr<Explosion>> explosions;

    std::unique_ptr<WallPositionsGenerator> gen;
    SimpleMap simpleMap;
    std::shared_ptr<physics::PhysicsEngine> ppool;
    std::shared_ptr<graphics::RendererPool> rpool;
};



