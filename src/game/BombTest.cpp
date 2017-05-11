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

TEST_F(BombTest, AfterDeltaTimeSmallerThenBombTimer_shouldDoNoting)
{
    using namespace std::chrono_literals;
    bomb.update(1ms);
}

TEST_F(BombTest, AfterCreation_shouldHasntExploded)
{
    ASSERT_FALSE(bomb.hasExploded());
}
