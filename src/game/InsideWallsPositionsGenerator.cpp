#include "InsideWallsPositionsGenerator.hpp"

#include "FieldSize.hpp"

inside_walls_positions_generator::Walls
inside_walls_positions_generator::generate_walls(
    BoundarySize boundary_size) const
{
    if (boundary_size.width > 0)
    {
        return {};
    }
    return {};
}