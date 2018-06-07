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
    DefautlBombFactory(physics::PhysicsEngine&,
                       graphics::RendererPool&);

    virtual std::unique_ptr<Bomb> create_time_bomb() const = 0;

private:
    physics::PhysicsEngine& physics_engine;
    graphics::RendererPool& renderer_pool;
};
