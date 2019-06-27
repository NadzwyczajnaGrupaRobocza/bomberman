#include "SimpleMap.hpp"

#include "FieldSize.hpp"
#include "boost/numeric/conversion/cast.hpp"
#include "boost/range/algorithm.hpp"

SimpleMap::SimpleMap(physics::PhysicsEngine& pEngine,
                     const WallPositionsGenerator& generated_walls_generator,
                     graphics::renderer_pool& rEngine, math::Size2u map_s)
    : physics_engine(pEngine), graphics_engine{rEngine}, map_size{
                                                             std::move(map_s)}
{
    constexpr graphics::color map_grey{161, 161, 161};
    const math::Size2f map_dimensions{
        boost::numeric_cast<float>(map_size.width),
        boost::numeric_cast<float>(map_size.height)};

    render_ids.push_back(graphics_engine.acquire(
        math::Size2f{scale_to_field_size(map_dimensions)},
        math::Position2f{0.0f, 0.0f}, map_grey));

    constexpr graphics::color wall_bronze{205, 127, 50};

    for (const auto& generated_walls :
         generated_walls_generator.generate_boundary_walls(map_size))
    {
        physics_ids.push_back(physics_engine.register_colider(
            {static_cast<float>(generated_walls.second.first),
             static_cast<float>(generated_walls.second.second)},
            {static_cast<float>(generated_walls.first.first),
             static_cast<float>(generated_walls.first.second)}));
        render_ids.push_back(graphics_engine.acquire(
            {static_cast<float>(generated_walls.second.first),
             static_cast<float>(generated_walls.second.second)},
            {static_cast<float>(generated_walls.first.first),
             static_cast<float>(generated_walls.first.second)},
            wall_bronze));
    }
}

SimpleMap::~SimpleMap()
{
    boost::for_each(render_ids,
                    [&](const auto id) { graphics_engine.release(id); });
    boost::for_each(physics_ids,
                    [&](const auto id) { physics_engine.deregister(id); });
}

ExplosionRange SimpleMap::get_explosion_range(std::pair<int, int> start_point,
                                              int range) const
{
    const auto left = get_range_in_decreasing_direction<LeftDistance>(
        start_point.first, range);
    const auto up = get_range_in_decreasing_direction<UpDistance>(
        start_point.second, range);
    const auto down = get_range_in_increasing_direction<DownDistance>(
        start_point.second, range, boost::numeric_cast<int>(map_size.height));
    const auto right = get_range_in_increasing_direction<RightDistance>(
        start_point.first, range, boost::numeric_cast<int>(map_size.width));
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
