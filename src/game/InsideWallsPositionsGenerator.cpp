#include "InsideWallsPositionsGenerator.hpp"

#include "FieldSize.hpp"
#include "range/v3/algorithm.hpp"

inside_walls_positions_generator::Walls
inside_walls_positions_generator::generate_walls(
    BoundarySize boundary_size) const
{
    validate_arguments(boundary_size);
    return {};
}

void inside_walls_positions_generator::validate_arguments(
    BoundarySize boundary_size)
{
    auto isOdd = [](int number) { return number % 2 != 0; };
    if (ranges::any_of({boundary_size.width, boundary_size.height}, isOdd))
    {
        throw unable_to_generate{"Can't generate internal walls with odd size"};
    }
}