#include "BoundaryWallsPositionsGenerator.hpp"

BoundaryWallsPositionsGenerator::Walls
    BoundaryWallsPositionsGenerator::generate_boundary_walls(BoundarySize boundary_size) const
{
    if (boundary_size == 0)
    {
        return {};
    }
    else
    {
        return {{{0, 0}, {0, boundary_size}},
                {{0, 0}, {boundary_size, 0}},
                {{boundary_size, 0}, {boundary_size, boundary_size}},
                {{0, boundary_size}, {boundary_size, boundary_size}}};
    }
}
