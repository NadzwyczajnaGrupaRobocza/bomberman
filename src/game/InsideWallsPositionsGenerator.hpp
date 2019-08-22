#pragma once

#include "WallPositionsGenerator.hpp"

class inside_walls_positions_generator : public WallPositionsGenerator
{
public:
    Walls generate_walls(BoundarySize) const;

private:
    static void validate_arguments(BoundarySize);
};
