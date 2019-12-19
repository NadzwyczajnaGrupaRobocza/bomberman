#include "WallPositionsGeneratorComposite.hpp"

wall_positions_generator_composite::wall_positions_generator_composite(
    Generators g)
    : generators{std::move(g)}
{
}

auto wall_positions_generator_composite::generate_walls(BoundarySize size) const
    -> Walls
{
    if (generators.empty())
    {
        return {};
    }
    return generators.front()->generate_walls(size);
}
