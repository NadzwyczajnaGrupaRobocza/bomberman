#include "gmock/gmock.h"

#include "FieldSize.hpp"
#include "InsideWallsPositionsGenerator.hpp"
#include "gtest/gtest.h"
#include "range/v3/all.hpp"

using namespace ::testing;

class InsideWallsPositionsGeneratorTest : public Test
{
public:
    InsideWallsPositionsGenerator generator;

    WallPositionsGenerator::Walls
    create_expected_walls(const WallPositionsGenerator::Walls& raw_walls)
    {
        const auto scale_with_field_size = [](const auto& wall) {
            return WallPositionsGenerator::Wall{
                {wall.first.first * field_size.width,
                 wall.first.second * field_size.height},
                {wall.second.first * field_size.width,
                 wall.second.second * field_size.height}};
        };
        return raw_walls | ranges::view::transform(scale_with_field_size);
    };
};

TEST_F(InsideWallsPositionsGeneratorTest, For0SizeShouldReturnNowWalls)
{
    ASSERT_THAT(generator.generate_walls({0, 0}), IsEmpty());
}

TEST_F(InsideWallsPositionsGeneratorTest, For1SizeShouldReturnOneWall)
{
    const WallPositionsGenerator::Walls expected_walls{
        {{0, 0}, {field_size.width, field_size.height}}};

    ASSERT_THAT(generator.generate_walls({1, 1}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(InsideWallsPositionsGeneratorTest, For5SizeShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls =
        create_expected_walls({{{0, 0}, {1, 5}},
                               {{0, 0}, {5, 1}},
                               {{4, 0}, {1, 5}},
                               {{0, 4}, {5, 1}}});

    ASSERT_THAT(generator.generate_walls({5, 5}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(InsideWallsPositionsGeneratorTest, For2SizeShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls{
        create_expected_walls({{{0, 0}, {1, 2}},
                               {{0, 0}, {2, 1}},
                               {{1, 0}, {1, 2}},
                               {{0, 1}, {2, 1}}})};

    ASSERT_THAT(generator.generate_walls({2, 2}),
                UnorderedElementsAreArray(expected_walls));
}

TEST_F(InsideWallsPositionsGeneratorTest, ForDifferentEdgesShouldReturnWalls)
{
    const WallPositionsGenerator::Walls expected_walls{
        create_expected_walls({{{0, 0}, {1, 8}},
                               {{0, 0}, {6, 1}},
                               {{5, 0}, {1, 8}},
                               {{0, 7}, {6, 1}}})};

    ASSERT_THAT(generator.generate_walls({6, 8}),
                UnorderedElementsAreArray(expected_walls));
}
