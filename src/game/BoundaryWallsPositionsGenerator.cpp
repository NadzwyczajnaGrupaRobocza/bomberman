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
   return  generate_empty_for_size_bigger_than_one(boundary_size);
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

BoundaryWallsPositionsGenerator::Walls BoundaryWallsPositionsGenerator::generate_walls_for_size_one()
{
    return {{{0, 0}, {1, 1}}};
}

BoundaryWallsPositionsGenerator::BoundaryWallsPositionsGenerator::Walls 
BoundaryWallsPositionsGenerator::generate_empty_for_size_bigger_than_one(
    BoundarySize boundary_size)
{
    return {{{0, 0}, {1, boundary_size}},
            {{0, 0}, {boundary_size, 1}},
            {{boundary_size - 1, 0}, {1, boundary_size}},
            {{0, boundary_size - 1}, {boundary_size, 1}}};
}
