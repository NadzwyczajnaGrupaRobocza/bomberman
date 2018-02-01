#pragma once

#include "WallPositionsGenerator.hpp"

class BoundaryWallsPositionsGenerator : public WallPositionsGenerator
{
public:
    Walls generate_boundary_walls(BoundarySize) const;

private:
    static bool zero_size(BoundarySize);
    static bool size_one(BoundarySize);
    static Walls generate_empty_walls();
    static Walls generate_walls_for_size_one();
    static Walls generate_empty_for_size_bigger_than_one(BoundarySize);
    static PositionInSpace position(BaseType, BaseType);
    static WallSize size(BaseType, BaseType);
};
