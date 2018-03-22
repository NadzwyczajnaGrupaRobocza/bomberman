#include <gtest/gtest.h>

#include <fakeit.hpp>

#include "Bomberman.hpp"

using namespace ::testing;
using namespace ::fakeit;
using namespace std::literals::chrono_literals;

class BombermanTest : public Test
{
public:
    void SetUp() override
    {
        Fake(Dtor(human_player));
        Fake(Dtor(physics_engine));
        Fake(Dtor(renderer_pool));
    }

    graphics::RendererId renderer_id{0x12};
    physics::PhysicsId physics_id{0x3F};

    Mock<HumanPlayer> human_player;
    Mock<physics::PhysicsEngine> physics_engine;
    Mock<graphics::RendererPool> renderer_pool;

    Bomberman bomberman{
        physics_id, renderer_id,
        std::unique_ptr<HumanPlayer>(&human_player.get()),
        std::shared_ptr<physics::PhysicsEngine>(&physics_engine.get()),
        std::shared_ptr<graphics::RendererPool>(&renderer_pool.get())};
};

TEST_F(BombermanTest, newlyCreatedBomermanShouldBeAlive)
{
    ASSERT_TRUE(bomberman.areYouDead());
}

TEST_F(BombermanTest, update)
{
    const math::Position2f bomberman_position{20.0f, 120.0f};
    const math::Position2f new_bomberman_position{21.0f, 121.0f};
    math::Position2f new_renderer_position{0.0f, 0.0f};
    math::Position2f new_physics_position{0.0f, 0.0f};
    const VectorInt2D player_direction = {1, 1};

    When(Method(physics_engine, get_position).Using(physics_id))
        .Return(bomberman_position);
    When(Method(renderer_pool, set_position))
        .Do([&new_renderer_position](const auto&, const auto& position) mutable {
            new_renderer_position = position;
        });
    When(Method(physics_engine, set_position))
        .Do([&new_physics_position](const auto&, const auto& position) mutable {
            new_physics_position = position;
        });

    When(Method(human_player, get_direction)).Return(player_direction);

    bomberman.update(3ms);

    Verify(Method(physics_engine, get_position).Using(physics_id));
    Verify(Method(renderer_pool, set_position).Using(renderer_id, _));
    Verify(Method(human_player, get_direction));
    Verify(Method(physics_engine, set_position).Using(physics_id, _));

    EXPECT_EQ(bomberman_position, new_renderer_position);
    EXPECT_EQ(new_bomberman_position, new_physics_position);
}
