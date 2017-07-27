#include "gtest/gtest.h"

#include "glm/glm.hpp"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.hpp"

class SimpleMap
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine) : physicsEngine(pEngine)
    {
        for (int i = 0; i < wallsCount; ++i)
        {
            physicsEngine.register_colider({}, {});
        }
    }

private:
    physics::PhysicsEngine& physicsEngine;
    std::vector<physics::PhysicsEngine> walls;
    const int wallsCount = 36;
};

//////////////////////////////////////////////////////////////////////////////////////////TEST

using namespace ::testing;
using namespace ::fakeit;

class SimpleMapConstructorExpectations : public Test
{
public:
    SimpleMapConstructorExpectations()
    {
        When(Method(physicsEngine, register_colider))
            .AlwaysDo([](const auto&, const auto&) {
                static unsigned id = 0;
                return physics::PhysicsId{id++};
            });
    }

    Mock<physics::PhysicsEngine> physicsEngine;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get()};
    const int wallsCount = 36;
};

TEST_F(SimpleMapTest, ShouldCreateWalls)
{
    Verify(Method(physicsEngine, register_colider)).Exactly(wallsCount);
}
