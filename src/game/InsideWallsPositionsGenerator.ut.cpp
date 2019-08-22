#include "gmock/gmock.h"

#include "FieldSize.hpp"
#include "InsideWallsPositionsGenerator.hpp"
#include "gtest/gtest.h"
#include "range/v3/all.hpp"

using namespace ::testing;

class inside_walls_positions_generator_test : public Test
{
public:
    inside_walls_positions_generator generator;
};

TEST_F(inside_walls_positions_generator_test, givenOddSize_shuoldThrow)
{
    constexpr auto oddValue = 3;
    constexpr auto evenValue = 4;
    ASSERT_THROW(generator.generate_walls({oddValue, evenValue}),
                 WallPositionsGenerator::unable_to_generate);
    ASSERT_THROW(generator.generate_walls({evenValue, oddValue}),
                 WallPositionsGenerator::unable_to_generate);
    ASSERT_THROW(generator.generate_walls({oddValue, oddValue}),
                 WallPositionsGenerator::unable_to_generate);
}