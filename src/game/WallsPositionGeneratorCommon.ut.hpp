#include "FieldSize.hpp"
#include "WallPositionsGenerator.hpp"
#include "range/v3/all.hpp"
#include "range/v3/range/conversion.hpp"

inline WallPositionsGenerator::Walls
create_expected_walls(const WallPositionsGenerator::Walls& raw_walls)
{
    const auto scale_with_field_size = [](const auto& wall) {
        return WallPositionsGenerator::Wall{
            {wall.first.first * field_size.width,
             wall.first.second * field_size.height},
            {wall.second.first * field_size.width,
             wall.second.second * field_size.height}};
    };
    return raw_walls | ranges::views::transform(scale_with_field_size) |
           ranges::to<std::vector>();
};

inline WallPositionsGenerator::Walls create_expected_one_square_walls(
    const std::initializer_list<WallPositionsGenerator::PositionInSpace>&
        raw_walls)
{
    const auto scale_with_field_size = [](const auto& wall) {
        static WallPositionsGenerator::WallSize one_field_wall{1, 1};
        return WallPositionsGenerator::Wall{
            {wall.first * field_size.width, wall.second * field_size.height},
            {one_field_wall.first * field_size.width,
             one_field_wall.second * field_size.height}};
    };
    return raw_walls | ranges::views::transform(scale_with_field_size) |
           ranges::to<std::vector>();
};
