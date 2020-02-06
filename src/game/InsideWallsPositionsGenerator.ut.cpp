#include "gmock/gmock.h"

#include "InsideWallsPositionsGenerator.hpp"
#include "WallsPositionGeneratorCommon.ut.hpp"
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

TEST_F(inside_walls_positions_generator_test, given5_shouldReturnOneWall)
{
    const auto expected_walls = create_expected_one_square_walls({{2, 2}});
    ASSERT_THAT(generator.generate_walls({5, 5}), Eq(expected_walls));
}

TEST_F(inside_walls_positions_generator_test, given6_shuoldReturnOneWall)
{
    const auto expected_walls = create_expected_one_square_walls({{2, 2}});
    ASSERT_THAT(generator.generate_walls({6, 6}), Eq(expected_walls));
}

TEST_F(inside_walls_positions_generator_test, given7And8_shuoldReturnFourWalls)
{
    const auto expected_walls =
        create_expected_one_square_walls({{2, 2}, {2, 4}, {4, 2}, {4, 4}});
    ASSERT_THAT(generator.generate_walls({7, 8}), Eq(expected_walls));
}

TEST_F(inside_walls_positions_generator_test, given7And6_shuoldReturnTwoWalls)
{
    const auto expected_walls =
        create_expected_one_square_walls({{2, 2}, {4, 2}});
    ASSERT_THAT(generator.generate_walls({7, 6}), Eq(expected_walls));
}
