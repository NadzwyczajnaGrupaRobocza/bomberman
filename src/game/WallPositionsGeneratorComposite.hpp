#pragma once

#include <memory>
#include <vector>

#include "WallPositionsGenerator.hpp"

class wall_positions_generator_composite : public WallPositionsGenerator
{
public:
    using Generators =
        std::vector<std::shared_ptr<const WallPositionsGenerator>>;
    wall_positions_generator_composite(Generators);
    Walls generate_walls(BoundarySize) const override;

private:
    const Generators generators;
};
