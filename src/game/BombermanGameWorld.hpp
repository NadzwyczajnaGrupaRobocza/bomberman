#pragma once

#include <boost/serialization/strong_typedef.hpp>
#include <map>
#include <memory>
#include <vector>

#include "Bomb.hpp"
#include "GameWorld.hpp"
#include "SimpleMap.hpp"
#include "graphics/renderer_pool.hpp"
#include "graphics/window_change_observer.hpp"
#include "math/Size2u.hpp"
#include "physics/PhysicsEngine.hpp"

class BombermanGameWorld : public GameWorld,
                           public graphics::window_change_observer
{
public:
    BombermanGameWorld(std::unique_ptr<physics::PhysicsEngine>,
                       std::unique_ptr<graphics::renderer_pool>,
                       const math::Size2u& map_size);

    bool is_bomb_at_pos(const BombPosition&) const override;

    void register_bomb(BombPosition, std::unique_ptr<Bomb>) override;
    void register_explosion(ExplosionPosition,
                            std::unique_ptr<Explosion>) override;

    void update(DeltaTime) override;
    void window_size_changed(const graphics::window_size&) override;

private:
    void cleanBombs();

    std::vector<std::unique_ptr<Entity>> entity;
    std::map<BombPosition, std::unique_ptr<Bomb>> bombs;
    std::map<ExplosionPosition, std::unique_ptr<Explosion>> explosions;

    std::unique_ptr<WallPositionsGenerator> gen;
    SimpleMap simpleMap;
    std::shared_ptr<physics::PhysicsEngine> ppool;
    std::shared_ptr<graphics::renderer_pool> rpool;
};
