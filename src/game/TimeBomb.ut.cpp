#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "physics/PhysicsEngine.mock.hpp"
#include "graphics/renderer_pool.mock.hpp"
#include "BombLauncher.mock.hpp"

#include "TimeBomb.hpp"

using namespace ::testing;

class ExpectRegistration
{
public:
    ExpectRegistration()
    {
        EXPECT_CALL(renderer_pool, acquire(bomb_size, bomb_position))
            .WillOnce(Return(bomb_render_id));
        EXPECT_CALL(physics_engine, register_colider(bomb_size, bomb_position))
            .WillOnce(Return(bomb_physics_id));
    }

    void expect_deregistration()
    {
        EXPECT_CALL(renderer_pool, release(bomb_render_id)).WillOnce(Return());
        EXPECT_CALL(physics_engine, deregister(bomb_physics_id))
            .WillOnce(Return());
    }

    StrictMock<physics::MockPhysicsEngine> physics_engine;
    StrictMock<graphics::mock_renderer_pool> renderer_pool;
    std::shared_ptr<MockBombLauncher> bomb_launcher =
        std::make_shared<StrictMock<MockBombLauncher>>();
    const math::Position2f bomb_position{5.0, 7.0};
    const math::Size2f bomb_size{1.0, 1.0};
    const graphics::renderer_id bomb_render_id{66};
    const physics::PhysicsId bomb_physics_id{88};
};

class TimeBombTest : public ExpectRegistration, public Test
{
public:
    TimeBombTest()
    {
        ON_CALL(*bomb_launcher, notify_exploded()).WillByDefault(Return());
    }

    void expect_notify_bomb_launcher()
    {
        EXPECT_CALL(*bomb_launcher, notify_exploded()).WillOnce(Return());
    }

    TimeBomb bomb{physics_engine, renderer_pool, bomb_position, bomb_launcher};
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
    expect_deregistration();

    using namespace std::chrono_literals;
    bomb.update(3100ms);

    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterDeltaTimeEqualToTimeBombTimer_shouldExplode)
{
    expect_notify_bomb_launcher();
    expect_deregistration();

    using namespace std::chrono_literals;
    bomb.update(3s);

    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterSumOfDeltaTimesEqualToTimeBombTimer_shouldExplode)
{
    using namespace std::chrono_literals;
    bomb.update(2s);

    expect_notify_bomb_launcher();
    expect_deregistration();
    bomb.update(1s);

    ASSERT_TRUE(bomb.hasExploded());
}
