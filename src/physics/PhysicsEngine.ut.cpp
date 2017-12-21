#include "gtest/gtest.h"

#include <glm/vec2.hpp>

#include "PhysicsEngine.hpp"

class ConcretePhysicsEngine : public physics::PhysicsEngine
{
public:
    void set_position(physics::PhysicsId, const Position&) override
    {
    }

    Position get_position(physics::PhysicsId) const override
    {
        return {};
    }

    void solve_colisions() override
    {
    }

    physics::PhysicsId register_colider(const Position&,
                                        const Position&) override
    {
        return {};
    }

    void deregister(physics::PhysicsId) override
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

TEST_F(PhysicsEngineInterfaceTest, ShouldHaveGetPositionFunction)
{
    auto testFunction = [](physics::PhysicsEngine& engineTested) {
        engineTested.get_position(physics::PhysicsId{});
    };
    testFunction(engine);
}

TEST_F(PhysicsEngineInterfaceTest, ShouldHaveSolveColisionsFunction)
{
    auto testFunction = [](physics::PhysicsEngine& engineTested) {
        engineTested.solve_colisions();
    };
    testFunction(engine);
}

TEST_F(PhysicsEngineInterfaceTest, ShouldHaveRegisterColiderFunction)
{
    auto testFunction = [](physics::PhysicsEngine& engineTested) {
        engineTested.register_colider(physics::PhysicsEngine::Position{},
                                      physics::PhysicsEngine::Position{});
    };
    testFunction(engine);
}

TEST_F(PhysicsEngineInterfaceTest, ShouldHaveDeegisterColiderFunction)
{
    auto testFunction = [](physics::PhysicsEngine& engineTested) {
        engineTested.deregister(physics::PhysicsId{1});
    };
    testFunction(engine);
}
