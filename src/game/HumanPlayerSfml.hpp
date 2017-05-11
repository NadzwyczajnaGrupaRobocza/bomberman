#pragma once

#include "HumanPlayer.hpp"

class HumanPlayerSfml : public HumanPlayer
{
public:
    HumanPlayerSfml();

    VectorInt2D get_direction();
    bool wants_bomb();
};
