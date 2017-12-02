#include "SimpleMap.hpp"

SimpleMap::SimpleMap(physics::PhysicsEngine& pEngine,
                     const WallPositionsGenerator& wall_positions_generator)
    : physics_engine(pEngine)
{
    for (const auto& wall_position :
         wall_positions_generator.generate_boundary_walls(map_size))
    {
        physics_engine.register_colider(
            {wall_position.first.first, wall_position.first.second},
            {wall_position.second.first, wall_position.second.second});
    }
}

ExplosionRange SimpleMap::get_explosion_range(std::pair<int, int> start_point,
                                              int range) const
{
    const auto left = get_range_in_decreasing_direction<LeftDistance>(
        start_point.first, range);
    const auto up =
        get_range_in_decreasing_direction<UpDistance>(start_point.second, range);
    const auto down = get_range_in_increasing_direction<DownDistance>(
        start_point.second, range);
    const auto right = get_range_in_increasing_direction<RightDistance>(
        start_point.first, range);
    return {left, right, up, down};
}

bool SimpleMap::can_move_backward(const int start_point, const int range)
{
    constexpr auto first_no_wall_field = 1;
    constexpr auto minumum_resonable_range = 0;
    return start_point > first_no_wall_field && range > minumum_resonable_range;
}

bool SimpleMap::can_move_forward(const int start_point, const int range,
                               const int map_size)
{
    constexpr auto distance_from_map_size_to_last_no_wall_field = 2;
    const auto last_no_wall_field =
        map_size - distance_from_map_size_to_last_no_wall_field;
    constexpr auto minumum_resonable_range = 0;
    return start_point < last_no_wall_field && range > minumum_resonable_range;
}
