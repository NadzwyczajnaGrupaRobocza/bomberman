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

    virtual void set_position(physics::PhysicsId, const Position&) = 0;
    virtual Position get_position(physics::PhysicsId) const = 0;
};
}
