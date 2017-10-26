#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "glm/glm.hpp"

#include "fakeit.hpp"

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
               std::tie(other.leftDist, other.rightDist, other.upDist, other.downDist);
    }

private:
    LeftDistance leftDist;
    RightDistance rightDist;
    UpDistance upDist;
    DownDistance downDist;
};

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
             wall_positions_generator.generateBoundaryWalls(10))
        {
            physicsEngine.register_colider(
                {wall_position.first.first, wall_position.first.second},
                {wall_position.second.first, wall_position.second.second});
        }
    }

    ExplosionRange get_explosion_range(std::pair<int, int> , int range)
    {
        return {LeftDistance{1} , RightDistance{1}, UpDistance{1}, DownDistance{1}};
    }

private:
    physics::PhysicsEngine& physicsEngine;
    std::vector<physics::PhysicsEngine> walls;
    const int wallsCount = 36;
    const WallPositionsGenerator::WallSize wallSize{1, 1};
};

//////////////////////////////////////////////////////////////////////////////////////////TEST

using namespace ::fakeit;

class SimpleMapConstructorExpectations : public ::testing::Test
{
public:
    SimpleMapConstructorExpectations()
    {
        When(Method(physicsEngine, register_colider))
            .AlwaysDo([&](const auto& position, const auto& size) {
                static unsigned id = 0;
                wallsPositions.push_back(position);
                wallsSizes.push_back(size);
                return physics::PhysicsId{id++};
            });
        Method(wallPosGenerator, generateBoundaryWalls).Using(boundarySize) =
            generatedWalls;
    }

    const int boundarySize = 10;
    const std::vector<physics::PhysicsEngine::Position> generatedWallsSizes{
        {1, 1}, {1, 2}, {4, 4}, {4, 67}};
    const std::vector<physics::PhysicsEngine::Position> generatedWallsPositions{
        {8, 7}, {2, 1}, {2, 8}, {88, 123}};
    const WallPositionsGenerator::Walls generatedWalls{{{8, 7}, {1, 1}},
                                                       {{2, 1}, {1, 2}},
                                                       {{2, 8}, {4, 4}},
                                                       {{88, 123}, {4, 67}}};
    Mock<physics::PhysicsEngine> physicsEngine;
    Mock<WallPositionsGenerator> wallPosGenerator;
    std::vector<physics::PhysicsEngine::Position> wallsPositions;
    std::vector<physics::PhysicsEngine::Position> wallsSizes;
};

class SimpleMapTest : public SimpleMapConstructorExpectations
{
public:
    SimpleMap map{physicsEngine.get(), wallPosGenerator.get()};

    void verifyAllWallsArePlacedCorrectly()
    {
        ASSERT_THAT(wallsPositions, ::testing::UnorderedElementsAreArray(
                                        generatedWallsPositions));
        ASSERT_THAT(wallsSizes,
                    ::testing::UnorderedElementsAreArray(generatedWallsSizes));
    }
};

TEST_F(SimpleMapTest, DuringConstruction_ShouldCreateWalls)
{
    Verify(Method(physicsEngine, register_colider))
        .Exactly(static_cast<int>(generatedWalls.size()));
    Verify(Method(wallPosGenerator, generateBoundaryWalls));
    verifyAllWallsArePlacedCorrectly();
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosion_WhenNoBoundaryWallHit)
{
    ExplosionRange expectedRange{1_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(2, 2), 1),
                ::testing::Eq(expectedRange));
}

TEST_F(SimpleMapTest,
       get_explosion_range_shouldReturnMaxExplosion_WithCustomRange)
{
    ExplosionRange expectedRange{0_left, 1_right, 1_up, 1_down};
    ASSERT_THAT(map.get_explosion_range(std::make_pair(3, 3), 2),
                ::testing::Eq(expectedRange));
}
