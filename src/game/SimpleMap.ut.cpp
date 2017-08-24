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
    using PositionInSpace = std::pair<float, float>;
    using WallSize = std::pair<float, float>;
    using BoundarySize = int;
    using WallsPositions = std::vector<PositionInSpace>;

    virtual ~WallPositionsGenerator() = default;
    virtual WallsPositions generateBoundaryWallsPosition(BoundarySize,
                                                         WallSize) const = 0;
};

class SimpleMap
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine,
              const WallPositionsGenerator& wall_positions_generator)
        : physicsEngine(pEngine)
    {
        for (const auto wall_position :
             wall_positions_generator.generateBoundaryWallsPosition(10,
                                                                    wallSize))
        {
            physicsEngine.register_colider(
                {wall_position.first, wall_position.second},
                {wallSize.first, wallSize.second});
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
    const WallPositionsGenerator::WallSize wallSize{5, 5};
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
        Method(wallPosGenerator, generateBoundaryWallsPosition)
            .Using(boundarySize, wallSize) = generatedWallsPositions;
    }

    const int boundarySize = 10;
    WallPositionsGenerator::WallSize wallSize{5, 5};
    WallPositionsGenerator::WallsPositions generatedWallsPositions;
    Mock<physics::PhysicsEngine> physicsEngine;
    Mock<WallPositionsGenerator> wallPosGenerator;
    std::vector<physics::PhysicsEngine::Position> wallsPositions;
    std::vector<physics::PhysicsEngine::Position> wallsSizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get(), wallPosGenerator.get()};
    physics::PhysicsEngine::Position wallSize{5, 5};

    void verifyAllWallsHasTheSameSize()
    {
        ASSERT_THAT(wallsSizes, ::testing::Each(wallSize));
    }

    void verifyAllWallsArePlacedInDifferentPlace()
    {
        std::sort(wallsPositions.begin(), wallsPositions.end(),
                  [](const auto& lhs, const auto& rhs) {
                      return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
                  });
        const auto oldEnd = wallsPositions.end();
        const auto newEnd =
            std::unique(wallsPositions.begin(), wallsPositions.end());
        ASSERT_THAT(newEnd, ::testing::Eq(oldEnd));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physicsEngine, register_colider))
        .Exactly(static_cast<int>(generatedWallsPositions.size()));
    Verify(Method(wallPosGenerator, generateBoundaryWallsPosition));
    verifyAllWallsHasTheSameSize();
    verifyAllWallsArePlacedInDifferentPlace();
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionWhenNoBoundaryWallHit)
{
    ExplosionRange expectedRange{1, 1, 1, 1};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(2, 2), 1),
                ::testing::Eq(expectedRange));
}
