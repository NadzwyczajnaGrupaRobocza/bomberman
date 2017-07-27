#include "gtest/gtest.h"
#include "gmock/gmock.h"

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
            physicsEngine.register_colider({i, 0}, wallSize);
        }
    }

private:
    physics::PhysicsEngine& physicsEngine;
    std::vector<physics::PhysicsEngine> walls;
    const int wallsCount = 36;
    physics::PhysicsEngine::Position wallSize{5, 5};
};

//////////////////////////////////////////////////////////////////////////////////////////TEST

using namespace ::fakeit;

class SimpleMapConstructorExpectations : public ::testing::Test
{
public:
    SimpleMapConstructorExpectations()
    {
        When(Method(physicsEngine, register_colider))
            .AlwaysDo([&](const auto& position, const auto& size) {
                static unsigned id = 0;
                wallsPositions.push_back(position);
                wallsSizes.push_back(size);
                return physics::PhysicsId{id++};
            });
    }

    Mock<physics::PhysicsEngine> physicsEngine;
    std::vector<physics::PhysicsEngine::Position> wallsPositions;
    std::vector<physics::PhysicsEngine::Position> wallsSizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get()};
    const int wallsCount = 36;
    physics::PhysicsEngine::Position wallSize{5, 5};

    void verifyAllWallsHasTheSameSize()
    {
        ASSERT_THAT(wallsSizes, ::testing::Each(wallSize));
    }

    void verifyAllWallsArePlacedInDifferentPlace()
    {
        std::sort(wallsPositions.begin(), wallsPositions.end(), [](const auto &lhs, const auto &rhs)
                  {
                      return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
                  });
        const auto oldEnd = wallsPositions.end();
        const auto newEnd = std::unique(wallsPositions.begin(), wallsPositions.end());
        ASSERT_THAT(newEnd, ::testing::Eq(oldEnd));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physicsEngine, register_colider)).Exactly(wallsCount);
    verifyAllWallsHasTheSameSize();
    verifyAllWallsArePlacedInDifferentPlace();
}
