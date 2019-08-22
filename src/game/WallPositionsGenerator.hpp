#pragma once

#include <utility>
#include <vector>

#include "math/Size2u.hpp"

class WallPositionsGenerator
{
public:
    using BaseType = unsigned;
    using PositionInSpace = std::pair<BaseType, BaseType>;
    using WallSize = std::pair<BaseType, BaseType>;
    using BoundarySize = math::Size2u;
    using Wall = std::pair<PositionInSpace, WallSize>;
    using Walls = std::vector<Wall>;

    virtual ~WallPositionsGenerator() = default;
    virtual Walls generate_walls(BoundarySize) const = 0;
};
