#pragma once

#include <memory>

#include "BombFactory.hpp"

namespace physics
{
class PhysicsEngine;
}

namespace graphics
{
class renderer_pool;
}

class DefautlBombFactory : public BombFactory
{
public:
    DefautlBombFactory(std::shared_ptr<physics::PhysicsEngine>,
                       std::shared_ptr<graphics::renderer_pool>);

    std::unique_ptr<Bomb>
        create_time_bomb(math::Position2f,
                         std::shared_ptr<BombLauncher>) const override;

private:
    std::shared_ptr<physics::PhysicsEngine> physics_engine;
    std::shared_ptr<graphics::renderer_pool> renderer_pool;
};
