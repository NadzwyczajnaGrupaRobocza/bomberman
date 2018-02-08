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
    const WallPositionsGenerator::Walls expected_walls{{{0, 0}, {1, 1}}};

    ASSERT_THAT(generator.generate_boundary_walls(1),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For5SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {1, 5}}, {{0, 0}, {5, 1}}, {{4, 0}, {1, 5}}, {{0, 4}, {5, 1}}};

    ASSERT_THAT(generator.generate_boundary_walls(5),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For2SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {1, 2}}, {{0, 0}, {2, 1}}, {{1, 0}, {1, 2}}, {{0, 1}, {2, 1}}};

    ASSERT_THAT(generator.generate_boundary_walls(2),
                UnorderedElementsAreArray(expected_walls));
}
