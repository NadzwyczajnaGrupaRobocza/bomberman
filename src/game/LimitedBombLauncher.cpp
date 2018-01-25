#include "LimitedBombLauncher.hpp"

LimitedBombLauncher::LimitedBombLauncher(const int maximumBombs)
    : maxBombs{maximumBombs}
{
}

bool LimitedBombLauncher::try_spawn_bomb(const math::Position2)
{

    return true;
}

void LimitedBombLauncher::notifyExploded()
{
}
