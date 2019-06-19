#pragma once

#include <utility>
#include <vector>

class WallPositionsGenerator
{
public:
    using BaseType = unsigned;
    using PositionInSpace = std::pair<BaseType, BaseType>;
    using WallSize = std::pair<BaseType, BaseType>;
    using BoundarySize = unsigned;
    using Wall = std::pair<PositionInSpace, WallSize>;
    using Walls = std::vector<Wall>;

    virtual ~WallPositionsGenerator() = default;
    virtual Walls generate_boundary_walls(BoundarySize) const = 0;
};
