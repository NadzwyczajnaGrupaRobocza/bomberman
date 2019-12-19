#pragma once

#include "WallPositionsGenerator.hpp"

class wall_positions_generator_composite : public WallPositionsGenerator
{
public:
    Walls generate_walls(BoundarySize) const override;
};
