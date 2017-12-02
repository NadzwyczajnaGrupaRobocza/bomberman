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
        When(Method(physics_engine, register_colider))
            .AlwaysDo([&](const auto& position, const auto& size) {
                static unsigned id = 0;
                walls_positions.push_back(position);
                walls_sizes.push_back(size);
                return physics::PhysicsId{id++};
            });
        Method(wall_positions_generator, generate_boundary_walls)
            .Using(boundary_size) = generated_walls;
    }

    const int boundary_size = 10;
    const std::vector<physics::PhysicsEngine::Position> generateed_walls_sizes{
        {1, 1}, {1, 2}, {4, 4}, {4, 67}};
    const std::vector<physics::PhysicsEngine::Position>
        generated_walls_positions{{8, 7}, {2, 1}, {2, 8}, {88, 123}};
    const WallPositionsGenerator::Walls generated_walls{{{8, 7}, {1, 1}},
                                                        {{2, 1}, {1, 2}},
                                                        {{2, 8}, {4, 4}},
                                                        {{88, 123}, {4, 67}}};
    Mock<physics::PhysicsEngine> physics_engine;
    Mock<WallPositionsGenerator> wall_positions_generator;
    std::vector<physics::PhysicsEngine::Position> walls_positions;
    std::vector<physics::PhysicsEngine::Position> walls_sizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physics_engine.get(), wall_positions_generator.get()};

    void verifyAllWallsArePlacedCorrectly()
    {
        ASSERT_THAT(walls_positions, ::testing::UnorderedElementsAreArray(
                                         generated_walls_positions));
        ASSERT_THAT(walls_sizes, ::testing::UnorderedElementsAreArray(
                                     generateed_walls_sizes));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physics_engine, register_colider))
        .Exactly(static_cast<int>(generated_walls.size()));
    Verify(Method(wall_positions_generator, generate_boundary_walls));
    verifyAllWallsArePlacedCorrectly();
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosion_WhenNoBoundaryWallHit)
{
    ExplosionRange expected_range{1_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(4, 4), 1),
                ::testing::Eq(expected_range));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosion_WhenBiggerRange)
{
    ExplosionRange expected_range{2_left, 2_right, 2_up, 2_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(4, 4), 2),
                ::testing::Eq(expected_range));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenRachLeftEnd)
{
    ExplosionRange expected_range{0_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(1, 2), 1),
                ::testing::Eq(expected_range));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenRachLeftUpEnd)
{
    ExplosionRange expected_range{2_left, 3_right, 0_up, 3_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(3, 1), 3),
                ::testing::Eq(expected_range));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenReachDownEnd)
{
    ExplosionRange expected_range{3_left, 3_right, 3_up, 2_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(5, 6), 3),
                ::testing::Eq(expected_range));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosionLimited_WhenReachRightEnd)
{
    ExplosionRange expected_range{3_left, 2_right, 3_up, 0_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(6, 9), 3),
                ::testing::Eq(expected_range));
}
