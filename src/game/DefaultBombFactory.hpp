#pragma once

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
    DefautlBombFactory(physics::PhysicsEngine&, graphics::renderer_pool&);

    std::unique_ptr<Bomb>
        create_time_bomb(math::Position2f,
                         std::shared_ptr<BombLauncher>) const override;

private:
    physics::PhysicsEngine& physics_engine;
    graphics::renderer_pool& renderer_pool;
};
