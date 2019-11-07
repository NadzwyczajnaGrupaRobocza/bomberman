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

TEST_F(inside_walls_positions_generator_test,
       givenSizeBelow5_ShouldNotGenerateAnyWalls)
{
    ASSERT_THAT(generator.generate_walls({0, 1}), IsEmpty());
    ASSERT_THAT(generator.generate_walls({2, 3}), IsEmpty());
    ASSERT_THAT(generator.generate_walls({4, 4}), IsEmpty());
}
