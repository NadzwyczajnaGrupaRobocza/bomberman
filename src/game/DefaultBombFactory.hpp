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
    DefautlBombFactory(const physics::PhysicsEngine&,
                       const graphics::RendererPool&);

    virtual std::unique_ptr<Bomb> create_time_bomb() const = 0;

private:
    const physics::PhysicsEngine& physics_engine;
    const graphics::RendererPool& renderer_pool;
};
