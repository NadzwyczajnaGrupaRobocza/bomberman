#include <gtest/gtest.h>

#include <fakeit.hpp>

#include "Bomberman.hpp"

using namespace ::testing;
using namespace ::fakeit;

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
    // When(Method(physics_engine, get_position()));
}
