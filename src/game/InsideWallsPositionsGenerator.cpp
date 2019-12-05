#include <iostream>

#include "FieldSize.hpp"
#include "InsideWallsPositionsGenerator.hpp"
#include "range/v3/algorithm.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view.hpp"

inside_walls_positions_generator::Walls
inside_walls_positions_generator::generate_walls(
    BoundarySize boundary_size) const
{
    constexpr auto border = 2u;
    constexpr auto first_wall = border;
    constexpr auto last_wall = border;
    const auto last_wall_x =
        boundary_size.width >= 5 ? boundary_size.width - last_wall : border;
    const auto last_wall_y =
        boundary_size.height >= 5 ? boundary_size.height - last_wall : border;

    using namespace ranges;
    std::cout << first_wall << "->" << last_wall_x << "\n";
    std::cout << first_wall << "->" << last_wall_y << "\n";
    auto xs = views::ints(first_wall, last_wall_x) | views::stride(2);
    auto ys = views::ints(first_wall, last_wall_y) | views::stride(2);
    return views::transform(xs,
                            [&](auto x) {
                                std::cout << "X:" << x << "\n";
                                return views::transform(ys, [x](auto y) {
                                    std::cout << "X2:" << x << "\n";
                                    return Wall{{x, y}, {1, 1}};
                                });
                            }) |
           views::join | to<std::vector>();
}
