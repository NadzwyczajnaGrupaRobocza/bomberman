#pragma once

#include "WallPositionsGenerator.hpp"

class BoundaryWallsPositionsGenerator : public WallPositionsGenerator
{
public:
    Walls generate_boundary_walls(BoundarySize) const;
};
