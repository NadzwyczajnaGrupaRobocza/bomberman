#pragma once

#include "PhysicsEngine.hpp"

namespace physics
{

class ConcretePhysicsEngine : public physics::PhysicsEngine
{
public:
    void set_position(physics::PhysicsId, const math::Position2f& p) override
    {
      pos = p;
    }

    math::Position2f get_position(physics::PhysicsId) const override
    {
        return pos;
    }

    void solve_colisions() override
    {
    }

    physics::PhysicsId register_colider(const math::Size2f&,
                                        const math::Position2f&) override
    {
        return {};
    }

    void deregister(physics::PhysicsId) override
    {
    }

 private:

  math::Position2f pos{0, 0};

};

}
