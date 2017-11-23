#include <tuple>
#include <vector>

#include "ExplosionRange.hpp"

#include "glm/glm.hpp"
#include "physics/PhysicsEngine.hpp"

class WallPositionsGenerator
{
public:
    using BaseType = int;
    using PositionInSpace = std::pair<BaseType, BaseType>;
    using WallSize = std::pair<BaseType, BaseType>;
    using BoundarySize = int;
    using Wall = std::pair<PositionInSpace, WallSize>;
    using Walls = std::vector<Wall>;

    virtual ~WallPositionsGenerator() = default;
    virtual Walls generateBoundaryWalls(BoundarySize) const = 0;
};

class SimpleMap
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine,
              const WallPositionsGenerator& wall_positions_generator);

    ExplosionRange get_explosion_range(std::pair<int, int> startPoint,
                                       int range) const;

private:
    physics::PhysicsEngine& physicsEngine;
    std::vector<physics::PhysicsEngine> walls;
    const int mapSize = 10;

    template <typename Distance>
    Distance get_range_in_decreasing_direction(const int startPoint,
                                               const int range) const
    {
        constexpr auto first_no_wall_field = 1;
        constexpr auto minumum_resonable_range = 0;
        if (startPoint > first_no_wall_field && range > minumum_resonable_range)
        {
            constexpr auto step = 1;
            return get_range_in_decreasing_direction<Distance>(
                       startPoint - step, range - step) +
                   Distance{step};
        }
        else
        {
            constexpr auto zeroRange = Distance{0};
            return zeroRange;
        }
    }

    template <typename Distance>
    Distance get_range_in_increasing_direction(const int startPoint,
                                               const int range) const
    {
        constexpr auto distance_from_map_size_to_last_no_wall_field = 2;
        const auto last_no_wall_field =
            mapSize - distance_from_map_size_to_last_no_wall_field;
        constexpr auto minumum_resonable_range = 0;
        if (startPoint < last_no_wall_field && range > minumum_resonable_range)
        {
            constexpr auto step = 1;
            return get_range_in_increasing_direction<Distance>(
                       startPoint + step, range - step) +
                   Distance{step};
        }
        else
        {
            constexpr auto zeroRange = Distance{0};
            return zeroRange;
        }
    }
};
