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
                physics_wall_positions.push_back(position);
                physics_wall_sizes.push_back(size);
                return physics::PhysicsId{id++};
            });
        Method(wall_positions_generator, generate_boundary_walls)
            .Using(edge_size) = generated_walls;
        When(Method(render_engine, register_renderable))
            .AlwaysDo([&](const auto& size, const auto& position) {
                static unsigned id = 0;
                render_wall_positions.push_back(position);
                render_wall_sizes.push_back(size);
                return graphics::RenderId{id++};
            });
        Method(render_engine, register_renderable)
            .Using(boundary_size, top_left_position) = backgroundId;
    }

    const int edge_size{10};
    const graphics::RenderEngine::Position top_left_position{0, 0};
    const graphics::RenderEngine::Position boundary_size{edge_size, edge_size};
    const std::vector<physics::PhysicsEngine::Position> generateed_walls_sizes{
        {1, 1}, {1, 2}, {4, 4}, {4, 67}};
    const std::vector<physics::PhysicsEngine::Position>
        generated_walls_positions{{8, 7}, {2, 1}, {2, 8}, {88, 123}};
    const WallPositionsGenerator::Walls generated_walls{{{8, 7}, {1, 1}},
                                                        {{2, 1}, {1, 2}},
                                                        {{2, 8}, {4, 4}},
                                                        {{88, 123}, {4, 67}}};
    Mock<physics::PhysicsEngine> physics_engine;
    Mock<graphics::RenderEngine> render_engine;
    Mock<WallPositionsGenerator> wall_positions_generator;
    std::vector<physics::PhysicsId> physicsIds;
    std::vector<physics::PhysicsEngine::Position> physics_wall_positions;
    std::vector<physics::PhysicsEngine::Position> physics_wall_sizes;
    std::vector<graphics::RenderId> renderIds;
    std::vector<graphics::RenderEngine::Position> render_wall_positions;
    std::vector<graphics::RenderEngine::Position> render_wall_sizes;
    graphics::RenderId backgroundId{1024};
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physics_engine.get(), wall_positions_generator.get(),
                  render_engine.get()};

    void verifyAllWallsArePlacedCorrectly()
    {
        ASSERT_THAT(
            physics_wall_positions,
            ::testing::UnorderedElementsAreArray(generated_walls_positions));
        ASSERT_THAT(physics_wall_sizes, ::testing::UnorderedElementsAreArray(
                                            generateed_walls_sizes));
        ASSERT_THAT(render_wall_positions, ::testing::UnorderedElementsAreArray(
                                               generated_walls_positions));
        ASSERT_THAT(render_wall_sizes, ::testing::UnorderedElementsAreArray(
                                           generateed_walls_sizes));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physics_engine, register_colider))
        .Exactly(static_cast<int>(generated_walls.size()));
    Verify(Method(wall_positions_generator, generate_boundary_walls));
    verifyAllWallsArePlacedCorrectly();
    Verify(Method(render_engine, register_renderable));
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
