#include "LimitedBombLauncher.hpp"

LimitedBombLauncher::LimitedBombLauncher(const int maximumBombs)
    : maxBombs{maximumBombs}
{
}

bool LimitedBombLauncher::try_spawn_bomb(const math::Position2)
{
    const auto bombCanBeSpawned = canSpawnBomb();
    if (bombCanBeSpawned)
    {
        launchBomb();
    }
    return bombCanBeSpawned;
}

bool LimitedBombLauncher::canSpawnBomb() const
{
    return maxBombs > bombs;
}

void LimitedBombLauncher::launchBomb()
{
    ++bombs;
}

void LimitedBombLauncher::notifyExploded()
{
}
