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
