#include "WallPositionsGenerator.mock.hpp"
#include "gmock/gmock.h"

#include "WallPositionsGeneratorComposite.hpp"

using namespace ::testing;

class wall_positions_generator_composite_test : public Test
{
public:
    WallPositionsGenerator::BoundarySize some_size{1, 2};
    WallPositionsGenerator::Walls first_walls{{{1, 2}, {3, 4}},
                                              {{1, 54}, {9, 3}}};
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
    std::shared_ptr<MockWallPositionsGenerator> other_generator = std::make_shared<MockWallPositionsGenerator>());
    wall_positions_generator_composite generator{{other_generator}};
};

TEST_F(wall_positions_generator_composite_with_one_generator_test,
       shuoldCallGeneratorAndReturnWhatItReturns)
{
    EXPECT_CALL(*other_generator, generate_walls(some_size))
        .WillOnce(Return(first_walls));

    ASSERT_THAT(generator.generate_walls(some_size), Eq(first_walls));
}
