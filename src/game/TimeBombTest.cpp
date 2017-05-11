#include "gtest/gtest.h"

#include "TimeBomb.hpp"

using namespace ::testing;

class TimeBombTest : public ::Test
{
public:
    TimeBomb bomb;
};

TEST_F(TimeBombTest, TimeBombIsNotDead)
{
    ASSERT_FALSE(bomb.areYouDead());
}

TEST_F(TimeBombTest, AfterDeltaTimeSmallerThenTimeBombTimer_shouldHasNotExploded)
{
    using namespace std::chrono_literals;
    bomb.update(1ms);
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
