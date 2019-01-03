#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.mock.hpp"
#include "graphics/RendererPool.mock.hpp"
#include "BombLauncher.hpp"

#include "TimeBomb.hpp"

using namespace ::fakeit;

class ExpectRegistration
{
public:
    ExpectRegistration()
    {
        Method(renderer_pool, acquire).Using(bomb_size, bomb_position) =
            bomb_render_id;
        Method(physics_engine, register_colider)
            .Using(bomb_size, bomb_position) = bomb_physics_id;
        Fake(Dtor(bomb_launcher));
    }

    ~ExpectRegistration()
    {
        Verify(Method(renderer_pool, acquire)).Exactly(oneTime);
        Verify(Method(physics_engine, register_colider)).Exactly(oneTime);
    }

    Mock<physics::PhysicsEngine> physics_engine;
    Mock<graphics::RendererPool> renderer_pool;
    Mock<BombLauncher> bomb_launcher;
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
        When(Method(bomb_launcher, notify_exploded)).Return();
    }

    void verify_notify_bomb_launcher()
    {
        Verify(Method(bomb_launcher, notify_exploded)).Exactly(1_Time);
    }

    TimeBomb bomb{physics_engine.get(), renderer_pool.get(), bomb_position,
    std::shared_ptr<BombLauncher>(&bomb_launcher.get())};
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
    
    using namespace std::chrono_literals;
    bomb.update(3100ms);

    ASSERT_TRUE(bomb.hasExploded());
    verify_notify_bomb_launcher();
}

TEST_F(TimeBombTest, AfterDeltaTimeEqualToTimeBombTimer_shouldExplode)
{
    using namespace std::chrono_literals;
    bomb.update(3s);

    ASSERT_TRUE(bomb.hasExploded());
    verify_notify_bomb_launcher();
}

TEST_F(TimeBombTest, AfterSumOfDeltaTimesEqualToTimeBombTimer_shouldExplode)
{
    using namespace std::chrono_literals;
    bomb.update(2s);
    bomb.update(1s);

    ASSERT_TRUE(bomb.hasExploded());
    verify_notify_bomb_launcher();
}
