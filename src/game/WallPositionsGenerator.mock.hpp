#pragma once

#include "WallPositionsGenerator.hpp"

class MockWallPositionsGenerator : public WallPositionsGenerator
{
    MOCK_CONST_METHOD1(generate_boundary_walls, Walls(BoundarySize));
};
