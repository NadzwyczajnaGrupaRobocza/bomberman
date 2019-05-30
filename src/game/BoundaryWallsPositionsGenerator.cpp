#include "BoundaryWallsPositionsGenerator.hpp"

BoundaryWallsPositionsGenerator::Walls
BoundaryWallsPositionsGenerator::generate_boundary_walls(
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

bool BoundaryWallsPositionsGenerator::zero_size(BoundarySize boundary_size)
{
    constexpr auto zero_size = 0;
    return boundary_size == zero_size;
}

bool BoundaryWallsPositionsGenerator::size_one(BoundarySize boundary_size)
{
    constexpr auto size_one = 1;
    return boundary_size == size_one;
}

BoundaryWallsPositionsGenerator::Walls
BoundaryWallsPositionsGenerator::generate_empty_walls()
{
    return {};
}

BoundaryWallsPositionsGenerator::Walls
BoundaryWallsPositionsGenerator::generate_walls_for_size_one()
{
    constexpr auto start_position = 0;
    constexpr auto wall_size = 20;
    return {
        {position(start_position, start_position), size(wall_size, wall_size)}};
}

BoundaryWallsPositionsGenerator::BoundaryWallsPositionsGenerator::Walls
BoundaryWallsPositionsGenerator::generate_empty_for_size_bigger_than_one(
    BoundarySize boundary_size)
{
    constexpr auto start_position = 0;
    constexpr auto minimum_size = 20;
    const auto just_before_end_position = boundary_size - 1;
    return {{position(start_position, start_position),
             size(minimum_size, boundary_size)},
            {position(start_position, start_position),
             size(boundary_size, minimum_size)},
            {position(just_before_end_position, start_position),
             size(minimum_size, boundary_size)},
            {position(start_position, just_before_end_position),
             size(boundary_size, minimum_size)}};
}

BoundaryWallsPositionsGenerator::PositionInSpace
BoundaryWallsPositionsGenerator::position(BaseType x, BaseType y)
{
    return {x, y};
}

BoundaryWallsPositionsGenerator::WallSize
BoundaryWallsPositionsGenerator::size(BaseType x, BaseType y)
{
    return {x, y};
}
