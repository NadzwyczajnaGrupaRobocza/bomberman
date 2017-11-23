#include "BoundaryWallsPositionsGenerator.hpp"

BoundaryWallsPositionsGenerator::Walls
    BoundaryWallsPositionsGenerator::generateBoundaryWalls(BoundarySize boundarySize) const
{
    if (boundarySize == 0)
    {
        return {};
    }
    else
    {
        return {{{0, 0}, {0, boundarySize}},
                {{0, 0}, {boundarySize, 0}},
                {{boundarySize, 0}, {boundarySize, boundarySize}},
                {{0, boundarySize}, {boundarySize, boundarySize}}};
    }
}
