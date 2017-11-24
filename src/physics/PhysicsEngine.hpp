#pragma once

#include "glm/fwd.hpp"

#include "PhysicsId.hpp"

namespace physics
{

class PhysicsEngine
{
public:
    using Position = glm::vec2;
    virtual ~PhysicsEngine() = default;

    virtual void set_position(PhysicsId, const Position&) = 0;
    virtual Position get_position(PhysicsId) const = 0;
    virtual void solve_colisions() = 0;
    virtual PhysicsId register_colider(const Position&, const Position&) = 0;
    virtual void deregister(PhysicsId) = 0;
};
}
