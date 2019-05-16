#pragma once

#include <boost/serialization/strong_typedef.hpp>
#include <map>
#include <memory>
#include <vector>

#include "Bomb.hpp"
#include "GameWorld.hpp"
#include "SimpleMap.hpp"
#include "graphics/renderer_pool.hpp"
#include "physics/PhysicsEngine.hpp"

class BombermanGameWorld : public GameWorld
{
public:
    BombermanGameWorld(std::unique_ptr<physics::PhysicsEngine>,
                       std::unique_ptr<graphics::renderer_pool>);

    bool is_bomb_at_pos(const BombPosition&) const override;

    void register_bomb(BombPosition, std::unique_ptr<Bomb>) override;
    void register_explosion(ExplosionPosition,
                            std::unique_ptr<Explosion>) override;

    void update(DeltaTime) override;

private:
    void cleanBombs();

    std::vector<std::unique_ptr<Entity>> entity;
    std::map<BombPosition, std::unique_ptr<Bomb>> bombs;
    std::map<ExplosionPosition, std::unique_ptr<Explosion>> explosions;

    int map_size = 100;
    std::unique_ptr<WallPositionsGenerator> gen;
    SimpleMap simpleMap;
    std::shared_ptr<physics::PhysicsEngine> ppool;
    std::shared_ptr<graphics::renderer_pool> rpool;
};
