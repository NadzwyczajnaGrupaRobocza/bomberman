#include "BoundaryWallsPositionsGenerator.hpp"

BoundaryWallsPositionsGenerator::Walls
BoundaryWallsPositionsGenerator::generate_boundary_walls(
    BoundarySize boundary_size) const
{
    if (boundary_size == 0)
    {
        return {};
    }
    if (boundary_size == 1)
    {
        return {{{0, 0}, {1,1}}};
    }
    return {{{0, 0}, {1, boundary_size}},
            {{0, 0}, {boundary_size, 1}},
            {{boundary_size -1 , 0}, {1, boundary_size}},
            {{0, boundary_size - 1}, {boundary_size, 1}}};
}
