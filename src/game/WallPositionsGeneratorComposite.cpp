#include "WallPositionsGeneratorComposite.hpp"
#include "range/v3/algorithm.hpp"
#include "range/v3/view.hpp"

wall_positions_generator_composite::wall_positions_generator_composite(
    Generators g)
    : generators{std::move(g)}
{
}

auto wall_positions_generator_composite::generate_walls(BoundarySize size) const
    -> Walls
{
    using namespace ranges;
    return views::transform(
               generators,
               [&](auto& generator) { generator->generate_walls(size); }) |
           views::join | to<std::vector>();
}
