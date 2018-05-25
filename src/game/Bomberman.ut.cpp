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

    void expectGetPosFromPhysics()
    {
        When(Method(physics_engine, get_position).Using(physics_id))
            .Return(current_position);
    }

    void expectSetCurrentPositionInRenderer()
    {
        When(Method(renderer_pool, set_position))
            .Do([this](const auto&, const auto& position) mutable {
                expected_current_renderer_position = position;
            });
    }

    void expectPassNewPositionToPhysics()
    {
        When(Method(physics_engine, set_position))
            .Do([this](const auto&, const auto& position) mutable {
                expected_next_physics_position = position;
            });
    }

    void expectGetDirectionFromInput(const VectorInt2D direction)
    {
        When(Method(human_player, get_direction)).Return(direction);
    }

    const math::Position2f current_position{20.0f, 120.0f};

    math::Position2f expected_current_renderer_position{0.0f, 0.0f};
    math::Position2f expected_next_physics_position{0.0f, 0.0f};

    graphics::RendererId renderer_id{{0x12}};
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
    ASSERT_FALSE(bomberman.areYouDead());
}

TEST_F(BombermanTest, update)
{
    expectGetPosFromPhysics();
    expectSetCurrentPositionInRenderer();
    expectGetDirectionFromInput(VectorInt2D{1, 1});
    expectPassNewPositionToPhysics();

    bomberman.update(DeltaTime{3ms});

    Verify(Method(physics_engine, get_position).Using(physics_id));
    Verify(Method(renderer_pool, set_position).Using(renderer_id, _));
    Verify(Method(human_player, get_direction));
    Verify(Method(physics_engine, set_position).Using(physics_id, _));

    EXPECT_EQ(current_position, expected_current_renderer_position);
    EXPECT_EQ(math::Position2f(20.003f, 120.003f), expected_next_physics_position);
}
