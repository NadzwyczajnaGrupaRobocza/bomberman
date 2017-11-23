#include "SimpleMap.hpp"

SimpleMap::SimpleMap(physics::PhysicsEngine& pEngine,
                     const WallPositionsGenerator& wall_positions_generator)
    : physicsEngine(pEngine)
{
    for (const auto& wall_position :
         wall_positions_generator.generateBoundaryWalls(mapSize))
    {
        physicsEngine.register_colider(
            {wall_position.first.first, wall_position.first.second},
            {wall_position.second.first, wall_position.second.second});
    }
}

ExplosionRange SimpleMap::get_explosion_range(std::pair<int, int> startPoint,
                                   int range) const
{
    const auto left = get_range_in_decreasing_direction<LeftDistance>(
        startPoint.first, range);
    const auto up =
        get_range_in_decreasing_direction<UpDistance>(startPoint.second, range);
    const auto down = get_range_in_increasing_direction<DownDistance>(
        startPoint.second, range);
    const auto right = get_range_in_increasing_direction<RightDistance>(
        startPoint.first, range);
    return {left, right, up, down};
}
