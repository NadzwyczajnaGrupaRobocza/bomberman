#include "WallPositionsGenerator.mock.hpp"
#include "gmock/gmock.h"

#include "WallPositionsGeneratorComposite.hpp"

using namespace ::testing;

class wall_positions_generator_composite_test : public Test
{
public:
    WallPositionsGenerator::BoundarySize some_size{1, 2};
    WallPositionsGenerator::Wall wall_one = {{1, 2}, {3, 4}};
    WallPositionsGenerator::Wall wall_two = {{1, 54}, {9, 3}};
    WallPositionsGenerator::Wall wall_three = {{1, 2}, {3, 4}};
    WallPositionsGenerator::Wall wall_four = {{1, 54}, {9, 3}};
    WallPositionsGenerator::Walls first_walls{wall_one, wall_two};
    WallPositionsGenerator::Walls second_walls{wall_three, wall_four};
    WallPositionsGenerator::Walls all_walls{wall_one, wall_two, wall_three,
                                            wall_four};
};

class empty_wall_positions_generator_composite_test
    : public wall_positions_generator_composite_test
{
public:
    wall_positions_generator_composite generator{{}};
};

TEST_F(empty_wall_positions_generator_composite_test, shouldNotThrow)
{
    ASSERT_NO_THROW(generator.generate_walls(some_size));
}

class wall_positions_generator_composite_with_one_generator_test
    : public wall_positions_generator_composite_test
{
public:
    std::shared_ptr<MockWallPositionsGenerator> other_generator =
        std::make_shared<MockWallPositionsGenerator>();
    wall_positions_generator_composite generator{{other_generator}};
};

TEST_F(wall_positions_generator_composite_with_one_generator_test,
       shuoldCallGeneratorAndReturnWhatItReturns)
{
    EXPECT_CALL(*other_generator, generate_walls(some_size))
        .WillOnce(Return(first_walls));

    ASSERT_THAT(generator.generate_walls(some_size), Eq(first_walls));
}

class wall_positions_generator_composite_with_two_generators_test
    : public wall_positions_generator_composite_test
{
public:
    std::shared_ptr<MockWallPositionsGenerator> first_generator =
        std::make_shared<MockWallPositionsGenerator>();
    std::shared_ptr<MockWallPositionsGenerator> second_generator =
        std::make_shared<MockWallPositionsGenerator>();
    wall_positions_generator_composite generator{
        {first_generator, second_generator}};
};

TEST_F(wall_positions_generator_composite_with_two_generators_test,
       shuoldCallAllGeneratorsAndReturnWhatItReturns)
{
    EXPECT_CALL(*first_generator, generate_walls(some_size))
        .WillOnce(Return(first_walls));
    EXPECT_CALL(*second_generator, generate_walls(some_size))
        .WillOnce(Return(second_walls));

    ASSERT_THAT(generator.generate_walls(some_size), Eq(all_walls));
}
