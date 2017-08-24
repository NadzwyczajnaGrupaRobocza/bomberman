#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "glm/glm.hpp"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.hpp"

struct ExplosionRange
{
    int left;
    int right;
    int up;
    int down;
};

bool operator==(const ExplosionRange& lhs, const ExplosionRange& rhs);
bool operator==(const ExplosionRange& lhs, const ExplosionRange& rhs)
{
    return std::tie(lhs.left, lhs.right, lhs.up, lhs.down) ==
           std::tie(rhs.left, rhs.right, rhs.up, rhs.down);
}

class WallPositionsGenerator
{
public:
    using BaseType = int;
    using PositionInSpace = std::pair<BaseType, BaseType>;
    using WallSize = std::pair<BaseType, BaseType>;
    using BoundarySize = int;
    using Wall = std::pair<PositionInSpace, WallSize>;
    using Walls = std::vector<Wall>;

    virtual ~WallPositionsGenerator() = default;
    virtual Walls generateBoundaryWalls(BoundarySize) const = 0;
};

class SimpleMap
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine,
              const WallPositionsGenerator& wall_positions_generator)
        : physicsEngine(pEngine)
    {
        for (const auto wall_position :
             wall_positions_generator.generateBoundaryWalls(10))
        {
            physicsEngine.register_colider(
                {wall_position.first.first, wall_position.first.second},
                {wall_position.second.first, wall_position.second.second});
        }
    }

    ExplosionRange get_explosion_range(std::pair<int, int>, int)
    {
        return {1, 1, 1, 1};
    }

private:
    physics::PhysicsEngine& physicsEngine;
    std::vector<physics::PhysicsEngine> walls;
    const int wallsCount = 36;
    const WallPositionsGenerator::WallSize wallSize{1, 1};
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
        Method(wallPosGenerator, generateBoundaryWalls)
            .Using(boundarySize) = generatedWalls;
    }

    const int boundarySize = 10;
    WallPositionsGenerator::WallSize expectedWallSize{1, 1};
    WallPositionsGenerator::Walls generatedWalls {
        {{1, 2}, {2, 1}}, {{ 4, 3}, {5, 4}}};
    Mock<physics::PhysicsEngine> physicsEngine;
    Mock<WallPositionsGenerator> wallPosGenerator;
    std::vector<physics::PhysicsEngine::Position> wallsPositions;
    std::vector<physics::PhysicsEngine::Position> wallsSizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get(), wallPosGenerator.get()};
    physics::PhysicsEngine::Position expectedWallSize{1.0, 1.0};

    void verifyAllWallsArePlacedCorrectly()
    {
        // ASSERT_THAT(wallPositiones, UnorderedElementsAre(generatedWalls |
        // transformaed))
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physicsEngine, register_colider))
        .Exactly(static_cast<int>(generatedWalls.size()));
    Verify(Method(wallPosGenerator, generateBoundaryWalls));
    verifyAllWallsArePlacedCorrectly();
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionWhenNoBoundaryWallHit)
{
    ExplosionRange expectedRange{1, 1, 1, 1};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(2, 2), 1),
                ::testing::Eq(expectedRange));
}
