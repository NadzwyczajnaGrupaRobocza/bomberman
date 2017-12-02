#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fakeit.hpp"

#include "BoundaryWallsPositionsGenerator.hpp"

using namespace ::fakeit;
using namespace ::testing;

class BoundaryWallsPositionsGeneratorTest : public Test
{
public:
    BoundaryWallsPositionsGenerator generator;
};

TEST_F(BoundaryWallsPositionsGeneratorTest, For0SizeShouldReturnNowWalls)
{
    ASSERT_THAT(generator.generate_boundary_walls(0), IsEmpty());
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For1SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {0, 1}}, {{0, 0}, {1, 0}}, {{1, 0}, {1, 1}}, {{0, 1}, {1, 1}}};

    ASSERT_THAT(generator.generate_boundary_walls(1), UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For5SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {0, 5}}, {{0, 0}, {5, 0}}, {{5, 0}, {5, 5}}, {{0, 5}, {5, 5}}};

    ASSERT_THAT(generator.generate_boundary_walls(5), UnorderedElementsAreArray(expected_walls));
}
