#include "gtest/gtest.h"

#include <glm/vec2.hpp>

#include "PhysicsEngine.hpp"

class ConcretePhysicsEngine : public physics::PhysicsEngine
{
public:
    void set_position(physics::PhysicsId, const glm::vec2&) override
    {
    }
};

using namespace ::testing;

class PhysicsEngineInterfaceTest : public Test
{
public:
    ConcretePhysicsEngine engine{};
};

TEST_F(PhysicsEngineInterfaceTest, ShouldCreateDeriveFromPhysicsEngine)
{
    auto testFunction = [](const physics::PhysicsEngine&) {};
    testFunction(engine);
}

TEST_F(PhysicsEngineInterfaceTest, ShouldHaveSetPositionFunction)
{
    auto testFunction = [](physics::PhysicsEngine& engineTested) {
        engineTested.set_position(physics::PhysicsId{}, glm::vec2{});
    };
    testFunction(engine);
}
