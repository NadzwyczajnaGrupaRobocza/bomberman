#pragma once

#include "math/Position2f.hpp"
#include "math/Size2f.hpp"

#include "PhysicsId.hpp"
#include "math/Position2f.hpp"

namespace physics
{

class PhysicsEngine
{
public:
    virtual ~PhysicsEngine() = default;

    virtual void set_position(PhysicsId, const math::Position2f&) = 0;
    virtual math::Position2f get_position(PhysicsId) const = 0;
    virtual void solve_colisions() = 0;
    virtual PhysicsId register_colider(const math::Size2f&,
                                       const math::Position2f&) = 0;
    virtual void deregister(PhysicsId) = 0;
};
}
