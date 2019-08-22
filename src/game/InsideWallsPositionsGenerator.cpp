#include "InsideWallsPositionsGenerator.hpp"

#include "FieldSize.hpp"

InsideWallsPositionsGenerator::Walls
InsideWallsPositionsGenerator::generate_walls(
    BoundarySize boundary_size) const
{
    if (zero_size(boundary_size))
    {
        return generate_empty_walls();
    }
    if (size_one(boundary_size))
    {
        return generate_walls_for_size_one();
    }
    return generate_empty_for_size_bigger_than_one(boundary_size);
}

bool InsideWallsPositionsGenerator::zero_size(BoundarySize boundary_size)
{
    constexpr auto zero_size = math::Size2u{0, 0};
    return boundary_size == zero_size;
}

bool InsideWallsPositionsGenerator::size_one(BoundarySize boundary_size)
{
    constexpr auto size_one = math::Size2u{1, 1};
    return boundary_size == size_one;
}

InsideWallsPositionsGenerator::Walls
InsideWallsPositionsGenerator::generate_empty_walls()
{
    return {};
}

InsideWallsPositionsGenerator::Walls
InsideWallsPositionsGenerator::generate_walls_for_size_one()
{
    constexpr auto start_position = 0;
    return {{position(start_position, start_position),
             size(field_size.width, field_size.height)}};
}

InsideWallsPositionsGenerator::InsideWallsPositionsGenerator::Walls
InsideWallsPositionsGenerator::generate_empty_for_size_bigger_than_one(
    BoundarySize boundary_size)
{
    constexpr auto start_position = 0;
    constexpr auto minimum_size = 1;
    const auto just_before_end_position_width =
        boundary_size.width - minimum_size;
    const auto just_before_end_position_height =
        boundary_size.height - minimum_size;
    return {{scale_to_field_size(position(start_position, start_position)),
             scale_to_field_size(size(minimum_size, boundary_size.height))},
            {scale_to_field_size(position(start_position, start_position)),
             scale_to_field_size(size(boundary_size.width, minimum_size))},
            {scale_to_field_size(
                 position(just_before_end_position_width, start_position)),
             scale_to_field_size(size(minimum_size, boundary_size.height))},
            {scale_to_field_size(
                 position(start_position, just_before_end_position_height)),
             scale_to_field_size(size(boundary_size.width, minimum_size))}};
}

InsideWallsPositionsGenerator::PositionInSpace
InsideWallsPositionsGenerator::position(BaseType x, BaseType y)
{
    return {x, y};
}

InsideWallsPositionsGenerator::WallSize
InsideWallsPositionsGenerator::size(BaseType x, BaseType y)
{
    return {x, y};
}
