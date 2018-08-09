#pragma once

#include "BombFactory.hpp"

namespace physics
{
class PhysicsEngine;
}

namespace graphics
{
class RendererPool;
}

class DefautlBombFactory : public BombFactory
{
public:
    DefautlBombFactory(physics::PhysicsEngine&, graphics::RendererPool&);

    std::unique_ptr<Bomb>
        create_time_bomb(math::Position2f,
                         std::shared_ptr<BombLauncher>) const override;

private:
    physics::PhysicsEngine& physics_engine;
    graphics::RendererPool& renderer_pool;
};
