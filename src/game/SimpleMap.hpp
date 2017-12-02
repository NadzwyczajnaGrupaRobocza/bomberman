#include <tuple>
#include <vector>

#include "ExplosionRange.hpp"
#include "WallPositionsGenerator.hpp"

#include "glm/glm.hpp"
#include "physics/PhysicsEngine.hpp"

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
        if (canMoveBackward(startPoint, range))
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

    static bool canMoveBackward(const int startPoint, const int range);

    template <typename Distance>
    Distance get_range_in_increasing_direction(const int startPoint,
                                               const int range) const
    {
        if (canMoveForward(startPoint, range, mapSize))
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

    static bool canMoveForward(const int startPoint, const int range,
                               const int mapSize);
};
