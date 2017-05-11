#include "gtest/gtest.h"

#include "Bomb.hpp"

using namespace ::testing;

class BombTest : public ::Test
{
public:
    Bomb bomb;
};

TEST_F(BombTest, BombIsNotDead)
{
    ASSERT_FALSE(bomb.areYouDead());
}

TEST_F(BombTest, AfterDeltaTimeSmallerThenBombTimer_shouldHasNotExploded)
{
    using namespace std::chrono_literals;
    bomb.update(1ms);
}

TEST_F(BombTest, AfterCreation_shouldHasntExploded)
{
    ASSERT_FALSE(bomb.hasExploded());
}

TEST_F(BombTest, AfterDeltaTimeBiggerThenBombTimer_shouldHasNotExploded)
{
    using namespace std::chrono_literals;
    bomb.update(3100ms);
    ASSERT_TRUE(bomb.hasExploded());
}

TEST_F(BombTest, AfterDeltaTimeEqualToBombTimer_shouldHasNotExploded)
{
    using namespace std::chrono_literals;
    bomb.update(3s);
    ASSERT_TRUE(bomb.hasExploded());
}
