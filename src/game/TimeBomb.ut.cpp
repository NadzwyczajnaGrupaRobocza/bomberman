#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.mock.hpp"
#include "graphics/RendererPool.mock.hpp"
#include "BombLauncher.mock.hpp"

#include "TimeBomb.hpp"

using namespace ::fakeit;

class ExpectRegistration
{
public:
    ExpectRegistration()
    {
        Method(renderer_pool, acquire).Using(bomb_size, bomb_position) =
            bomb_render_id;
        EXPECT_CALL(physics_engine, register_colider(bomb_size, bomb_position))
            .WillOnce(::testing::Return(bomb_physics_id));
    }

    ~ExpectRegistration()
    {
        Verify(Method(renderer_pool, acquire)).Exactly(oneTime);
    }

    physics::MockPhysicsEngine physics_engine;
    Mock<graphics::RendererPool> renderer_pool;
    graphics::MockRendererPool renderer_pool2;
    std::shared_ptr<MockBombLauncher> bomb_launcher =
        std::make_shared<MockBombLauncher>();
    const math::Position2f bomb_position{5.0, 7.0};
    const math::Size2f bomb_size{1.0, 1.0};
    const graphics::RendererId bomb_render_id{66};
    const physics::PhysicsId bomb_physics_id{88};
    const int oneTime{1};
};

class TimeBombTest : public ExpectRegistration, public ::testing::Test
{
public:
    TimeBombTest()
    {
        ON_CALL(*bomb_launcher, notify_exploded())
            .WillByDefault(::testing::Return());
    }

    void expect_notify_bomb_launcher()
    {
        EXPECT_CALL(*bomb_launcher, notify_exploded())
            .WillOnce(::testing::Return());
    }

    TimeBomb bomb{physics_engine, renderer_pool.get(), bomb_position,
                  bomb_launcher};
};

TEST_F(TimeBombTest, TimeBombIsNotDead)
{
    ASSERT_FALSE(bomb.areYouDead());
}

TEST_F(TimeBombTest,
       AfterDeltaTimeSmallerThenTimeBombTimer_shouldHasNotExploded)
{
    using namespace std::chrono_literals;
    bomb.update(1ms);
    ASSERT_FALSE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterCreation_shouldHasntExploded)
{
    ASSERT_FALSE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterDeltaTimeBiggerThenTimeBombTimer_shouldExplode)
{
    expect_notify_bomb_launcher();

    using namespace std::chrono_literals;
    bomb.update(3100ms);

    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterDeltaTimeEqualToTimeBombTimer_shouldExplode)
{
    expect_notify_bomb_launcher();

    using namespace std::chrono_literals;
    bomb.update(3s);

    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterSumOfDeltaTimesEqualToTimeBombTimer_shouldExplode)
{
    expect_notify_bomb_launcher();

    using namespace std::chrono_literals;
    bomb.update(2s);
    bomb.update(1s);

    ASSERT_TRUE(bomb.hasExploded());
}
