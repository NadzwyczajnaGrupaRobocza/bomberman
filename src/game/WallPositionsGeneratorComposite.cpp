#include "WallPositionsGeneratorComposite.hpp"
#include "range/v3/action.hpp"
#include "range/v3/algorithm.hpp"
#include "range/v3/range/conversion.hpp"
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
    return actions::join(generators |
                         views::transform([&](const auto& generator) {
                             return generator->generate_walls(size);
                         }));
}
