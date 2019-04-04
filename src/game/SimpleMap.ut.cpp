#include "gmock/gmock.h"

#include "glm/glm.hpp"
#include <vector>

#include "WallPositionsGenerator.mock.hpp"
#include "fakeit.hpp"
#include "graphics/renderer_pool.mock.hpp"
#include "physics/PhysicsEngine.mock.hpp"

#include "SimpleMap.hpp"

using namespace ::fakeit;

class SimpleMapConstructorExpectations : public ::testing::Test
{
public:
    SimpleMapConstructorExpectations()
    {
        EXPECT_CALL(physics_engine_mock,
                    register_colider(testing::_, testing::_))
            .WillRepeatedly(
                testing::Invoke([&](const auto& size, const auto& position) {
                    static uint8_t id = 0;
                    physics_wall_positions.push_back(position);
                    physics_wall_sizes.push_back(size);
                    const auto pid = physics::PhysicsId{id++};
                    physicsIds.push_back(pid);
                    return pid;
                }));
        EXPECT_CALL(physics_engine_mock, deregister(testing::_))
            .WillRepeatedly(testing::Invoke([&](const auto id) {
                deregistered_physics_ids.push_back(id);
            }));
        Method(wall_positions_generator, generate_boundary_walls)
            .Using(edge_size) = generated_walls;
        EXPECT_CALL(render_engine_mock,
                    acquire(testing::_, testing::_, testing::_))
            .WillRepeatedly(testing::Invoke(
                [&](const auto& size, const auto& position, const auto& color) {
                    static uint8_t id = 0;
                    render_wall_positions.push_back(position);
                    render_wall_sizes.push_back(size);
                    wall_colors.push_back(color);
                    const auto rid = graphics::renderer_id{{id++}};
                    render_ids.push_back(rid);
                    return rid;
                }));
        EXPECT_CALL(render_engine_mock, release(testing::_))
            .WillRepeatedly(testing::Invoke(
                [&](const auto id) { deregistered_render_ids.push_back(id); }));
        constexpr graphics::color map_grey{161, 161, 161};
        EXPECT_CALL(render_engine_mock,
                    acquire(boundary_size, top_left_position, map_grey))
            .WillRepeatedly(testing::Return(background_id));
        render_ids.push_back(background_id);
    }

    const int edge_size{10};
    const math::Position2f top_left_position{0, 0};
    const math::Size2f boundary_size{static_cast<float>(edge_size),
                                     static_cast<float>(edge_size)};
    const std::vector<math::Size2f> generated_walls_sizes{
        {1, 1}, {1, 2}, {4, 4}, {4, 67}};

    const std::vector<math::Position2f> generated_walls_positions{
        {8, 7}, {2, 1}, {2, 8}, {88, 123}};

    const WallPositionsGenerator::Walls generated_walls{{{8, 7}, {1, 1}},
                                                        {{2, 1}, {1, 2}},
                                                        {{2, 8}, {4, 4}},
                                                        {{88, 123}, {4, 67}}};
    testing::StrictMock<physics::MockPhysicsEngine> physics_engine_mock;
    testing::StrictMock<graphics::mock_renderer_pool> render_engine_mock;
    Mock<WallPositionsGenerator> wall_positions_generator;
    testing::StrictMock<MockWallPositionsGenerator>
        wall_positions_generator_mock;
    std::vector<physics::PhysicsId> physicsIds;
    std::vector<physics::PhysicsId> deregistered_physics_ids;
    std::vector<math::Position2f> physics_wall_positions;
    std::vector<math::Size2f> physics_wall_sizes;
    std::vector<graphics::renderer_id> render_ids;
    std::vector<math::Position2f> render_wall_positions;
    std::vector<math::Size2f> render_wall_sizes;
    std::vector<graphics::color> wall_colors;
    std::vector<graphics::renderer_id> deregistered_render_ids;
    graphics::renderer_id background_id{{uint8_t(1024)}};
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physics_engine_mock, wall_positions_generator.get(),
                  render_engine_mock};

    void verifyAllWallsArePlacedCorrectly()
    {
        ASSERT_THAT(
            physics_wall_positions,
            ::testing::UnorderedElementsAreArray(generated_walls_positions));
        ASSERT_THAT(physics_wall_sizes, ::testing::UnorderedElementsAreArray(
                                            generated_walls_sizes));
        ASSERT_THAT(render_wall_positions, ::testing::UnorderedElementsAreArray(
                                               generated_walls_positions));
        ASSERT_THAT(render_wall_sizes, ::testing::UnorderedElementsAreArray(
                                           generated_walls_sizes));

        constexpr graphics::color wall_bronze{205, 127, 50};
        ASSERT_THAT(wall_colors, ::testing::Each(wall_bronze));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
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

class SimpleMapWithoutImplicitConstructionTest
    : public SimpleMapConstructorExpectations
{
};

TEST_F(SimpleMapWithoutImplicitConstructionTest,
       DuringDestruction_ShouldUnredisterWalls)
{
    {
        SimpleMap map_destructor_test{physics_engine_mock,
                                      wall_positions_generator.get(),
                                      render_engine_mock};
    }
    ASSERT_THAT(deregistered_render_ids,
                ::testing::UnorderedElementsAreArray(render_ids));
    ASSERT_THAT(deregistered_physics_ids,
                ::testing::UnorderedElementsAreArray(physicsIds));
}
