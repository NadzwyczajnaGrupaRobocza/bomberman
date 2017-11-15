#include <tuple>
#include <vector>

#include "glm/glm.hpp"
#include "physics/PhysicsEngine.hpp"

enum class Direction
{
    up,
    down,
    left,
    right
};

template <typename T, Direction diretction>
struct Distance
{
    Distance() = default;
    constexpr explicit Distance(int d) : distance{d}
    {
    }

    operator int() const
    {
        return distance;
    }

    Distance operator+=(Distance other)
    {
        distance += other.distance;
        return *this;
    }

    Distance operator+(Distance other)
    {
        auto dist = *this;
        return dist += other;
    }

private:
    int distance;
};

using LeftDistance = Distance<int, Direction::left>;
using RightDistance = Distance<int, Direction::right>;
using UpDistance = Distance<int, Direction::up>;
using DownDistance = Distance<int, Direction::down>;

constexpr LeftDistance operator"" _left(unsigned long long int d)
{
    return LeftDistance{static_cast<int>(d)};
}
constexpr RightDistance operator"" _right(unsigned long long int d)
{
    return RightDistance{static_cast<int>(d)};
}
constexpr UpDistance operator"" _up(unsigned long long int d)
{
    return UpDistance{static_cast<int>(d)};
}
constexpr DownDistance operator"" _down(unsigned long long int d)
{
    return DownDistance{static_cast<int>(d)};
}

class ExplosionRange
{
public:
    ExplosionRange(LeftDistance left, RightDistance right, UpDistance up,
                   DownDistance down)
        : leftDist{left}, rightDist{right}, upDist{up}, downDist{down}
    {
    }

    LeftDistance left() const
    {
        return leftDist;
    }

    RightDistance right() const
    {
        return rightDist;
    }

    UpDistance up() const
    {
        return upDist;
    }

    DownDistance down() const
    {
        return downDist;
    }

    bool operator==(const ExplosionRange& other) const
    {
        return std::tie(leftDist, rightDist, upDist, downDist) ==
               std::tie(other.leftDist, other.rightDist, other.upDist,
                        other.downDist);
    }

private:
    LeftDistance leftDist;
    RightDistance rightDist;
    UpDistance upDist;
    DownDistance downDist;
};

std::ostream& operator<<(std::ostream& out, const ExplosionRange& range);
std::ostream& operator<<(std::ostream& out, const ExplosionRange& range)
{
    out << "{";
    out << "Left: " << range.left() << " ,";
    out << "Right: " << range.right() << " ,";
    out << "Up: " << range.up() << " ,";
    out << "Down: " << range.down();
    out << "}";
    return out;
}

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
              const WallPositionsGenerator& wall_positions_generator)
        : physicsEngine(pEngine)
    {
        for (const auto wall_position :
             wall_positions_generator.generateBoundaryWalls(mapSize))
        {
            physicsEngine.register_colider(
                {wall_position.first.first, wall_position.first.second},
                {wall_position.second.first, wall_position.second.second});
        }
    }

    ExplosionRange get_explosion_range(std::pair<int, int> startPoint,
                                       int range) const
    {
        const auto left = get_range_in_decreasing_direction<LeftDistance>(
            startPoint.first, range);
        const auto up = get_range_in_decreasing_direction<UpDistance>(
            startPoint.second, range);
        const auto down = get_range_in_increasing_direction<DownDistance>(
            startPoint.second, range);
        const auto right = get_range_in_increasing_direction<RightDistance>(
            startPoint.first, range);
        return {left, right, up, down};
    }

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
