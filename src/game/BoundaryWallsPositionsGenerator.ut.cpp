#include "gmock/gmock.h"

#include "BoundaryWallsPositionsGenerator.hpp"
#include "WallsPositionGeneratorCommon.ut.hpp"
#include "gtest/gtest.h"

using namespace ::testing;

class BoundaryWallsPositionsGeneratorTest : public Test
{
public:
    BoundaryWallsPositionsGenerator generator;
};

TEST_F(BoundaryWallsPositionsGeneratorTest, For0SizeShouldReturnNowWalls)
{
    ASSERT_THAT(generator.generate_walls({0, 0}), IsEmpty());
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For1SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {field_size.width, field_size.height}}};

    ASSERT_THAT(generator.generate_walls({1, 1}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For5SizeShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls =
        create_expected_walls({{{0, 0}, {1, 5}},
                               {{0, 0}, {5, 1}},
                               {{4, 0}, {1, 5}},
                               {{0, 4}, {5, 1}}});

    ASSERT_THAT(generator.generate_walls({5, 5}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, For2SizeShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls{
        create_expected_walls({{{0, 0}, {1, 2}},
                               {{0, 0}, {2, 1}},
                               {{1, 0}, {1, 2}},
                               {{0, 1}, {2, 1}}})};

    ASSERT_THAT(generator.generate_walls({2, 2}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(BoundaryWallsPositionsGeneratorTest, ForDifferentEdgesShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls{
        create_expected_walls({{{0, 0}, {1, 8}},
                               {{0, 0}, {6, 1}},
                               {{5, 0}, {1, 8}},
                               {{0, 7}, {6, 1}}})};

    ASSERT_THAT(generator.generate_walls({6, 8}),
                UnorderedElementsAreArray(expected_walls));
}
