#pragma once

#include "WallPositionsGenerator.hpp"

class BoundaryWallsPositionsGenerator : public WallPositionsGenerator
{
public:
    Walls generateBoundaryWalls(BoundarySize) const;
    
};
