#include "gtest/gtest.h"

#include "PhysicsEngine.hpp"

class ConcretePhysicsEngine : public physics::PhysicsEngine
{
};

TEST(PhysicsEngineInterfaceTest, ShouldCreateDeriveFromPhysicsEngine)
{
    auto testFunction = [](const physics::PhysicsEngine&) {
    };
    testFunction(ConcretePhysicsEngine{});
}
