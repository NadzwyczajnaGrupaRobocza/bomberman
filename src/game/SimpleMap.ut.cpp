#include "gtest/gtest.h"

#include "glm/glm.hpp"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.hpp"

class SimpleMap
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine) : physicsEngine(pEngine)
    {
        physicsEngine.register_colider({}, {});
    }

private:
    physics::PhysicsEngine& physicsEngine;
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
            .Return(physics::PhysicsId{1});
    }

    Mock<physics::PhysicsEngine> physicsEngine;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get()};
};

TEST_F(SimpleMapTest, Dummy)
{
    Verify(Method(physicsEngine, register_colider));
}
