#pragma once

#include "gmock/gmock.h"

#include "physics/PhysicsEngine.hpp"

namespace physics
{

class MockPhysicsEngine : public PhysicsEngine
{
public:
    MOCK_METHOD2(set_position, void(PhysicsId, const math::Position2f&));
    MOCK_CONST_METHOD1(get_position, math::Position2f(PhysicsId));
    MOCK_METHOD0(solve_colisions, void());
    MOCK_METHOD2(register_colider,
                 PhysicsId(const math::Size2f&, const math::Position2f&));
    MOCK_METHOD1(deregister, void(PhysicsId));
};
}
