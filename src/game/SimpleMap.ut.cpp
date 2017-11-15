#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "glm/glm.hpp"

#include "fakeit.hpp"

#include "SimpleMap.hpp"

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
        Method(wallPosGenerator, generateBoundaryWalls).Using(boundarySize) =
            generatedWalls;
    }

    const int boundarySize = 10;
    const std::vector<physics::PhysicsEngine::Position> generatedWallsSizes{
        {1, 1}, {1, 2}, {4, 4}, {4, 67}};
    const std::vector<physics::PhysicsEngine::Position> generatedWallsPositions{
        {8, 7}, {2, 1}, {2, 8}, {88, 123}};
    const WallPositionsGenerator::Walls generatedWalls{{{8, 7}, {1, 1}},
                                                       {{2, 1}, {1, 2}},
                                                       {{2, 8}, {4, 4}},
                                                       {{88, 123}, {4, 67}}};
    Mock<physics::PhysicsEngine> physicsEngine;
    Mock<WallPositionsGenerator> wallPosGenerator;
    std::vector<physics::PhysicsEngine::Position> wallsPositions;
    std::vector<physics::PhysicsEngine::Position> wallsSizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get(), wallPosGenerator.get()};

    void verifyAllWallsArePlacedCorrectly()
    {
        ASSERT_THAT(wallsPositions, ::testing::UnorderedElementsAreArray(
                                        generatedWallsPositions));
        ASSERT_THAT(wallsSizes,
                    ::testing::UnorderedElementsAreArray(generatedWallsSizes));
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
       get_explosion_range_shouldReturnMaxExplosion_WhenNoBoundaryWallHit)
{
    ExplosionRange expectedRange{1_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(4, 4), 1),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosion_WhenBiggerRange)
{
    ExplosionRange expectedRange{2_left, 2_right, 2_up, 2_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(4, 4), 2),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenRachLeftEnd)
{
    ExplosionRange expectedRange{0_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(1, 2), 1),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenRachLeftUpEnd)
{
    ExplosionRange expectedRange{2_left, 3_right, 0_up, 3_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(3, 1), 3),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenReachDownEnd)
{
    ExplosionRange expectedRange{3_left, 3_right, 3_up, 2_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(5, 6), 3),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenReachRightEnd)
{
    ExplosionRange expectedRange{3_left, 2_right, 3_up, 0_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(6, 9), 3),
                ::testing::Eq(expectedRange));
}
