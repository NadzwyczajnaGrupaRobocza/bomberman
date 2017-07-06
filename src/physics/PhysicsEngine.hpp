#pragma once

#include "glm/fwd.hpp"

#include "PhysicsId.hpp"

namespace physics
{

class PhysicsEngine
{
public:
    virtual ~PhysicsEngine() = default;

    virtual void set_position(physics::PhysicsId, const glm::vec2&) = 0;
};
}
