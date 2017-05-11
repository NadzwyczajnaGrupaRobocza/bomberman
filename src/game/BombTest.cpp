#include "gtest/gtest.h"

#include "Bomb.hpp"

using namespace ::testing;

TEST(BombTest, BombIsNotDead)
{
    ASSERT_FALSE(Bomb{}.areYouDead());
}
