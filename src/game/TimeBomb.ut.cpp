#include "gtest/gtest.h"

#include "fakeit.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"

#include "TimeBomb.hpp"

using namespace ::fakeit;

class ExpectRegistration
{
public:
    ExpectRegistration(Mock<physics::PhysicsEngine>&,
                       Mock<graphics::RendererPool>&)
    {
    }
};

class TimeBombTest : public ::testing::Test
{
public:
    Mock<physics::PhysicsEngine> physics_engine;
    Mock<graphics::RendererPool> renderer_pool;
    ExpectRegistration regisration_guard{physics_engine, renderer_pool};
    TimeBomb bomb{physics_engine.get(), renderer_pool.get()};
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
}

TEST_F(TimeBombTest, AfterDeltaTimeEqualToTimeBombTimer_shouldExplode)
{
    using namespace std::chrono_literals;
    bomb.update(3s);
    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(TimeBombTest, AfterSumOfDeltaTimesEqualToTimeBombTimer_shouldExplode)
{
    using namespace std::chrono_literals;
    bomb.update(2s);
    bomb.update(1s);
    ASSERT_TRUE(bomb.hasExploded());
}
