#include "gmock/gmock.h"

#include "WallPositionsGeneratorComposite.hpp"

using namespace ::testing;

class wall_positions_generator_composite_test : public Test
{
public:
    WallPositionsGenerator::BoundarySize some_size{1, 2};
};

class empty_wall_positions_generator_composite_test
    : public wall_positions_generator_composite_test
{
public:
    wall_positions_generator_composite generator{};
};

TEST_F(empty_wall_positions_generator_composite_test, shouldNotThrow)
{
    ASSERT_NO_THROW(generator.generate_walls(some_size));
}
