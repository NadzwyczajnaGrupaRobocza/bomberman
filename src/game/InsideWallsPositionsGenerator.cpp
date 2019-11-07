#include "FieldSize.hpp"
#include "InsideWallsPositionsGenerator.hpp"
#include "range/v3/algorithm.hpp"

inside_walls_positions_generator::Walls
    inside_walls_positions_generator::generate_walls(
        BoundarySize /*boundary_size*/) const
{
    return {};
}
