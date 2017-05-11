#pragma once

#include "HumanPlayer.hpp"

class HumanPlayerSfml : public HumanPlayer
{
public:
    VectorInt2D get_direction() const override;
    bool wants_bomb() const override;
};
