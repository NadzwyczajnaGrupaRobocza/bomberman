#include "LimitedBombLauncher.hpp"

#include "GameWorld.hpp"

LimitedBombLauncher::LimitedBombLauncher(std::shared_ptr<GameWorld> gw,
                                         const int maximum_bombs)
    : game_world{std::move(gw)},
      max_bombs{maximum_bombs}
{
}

bool LimitedBombLauncher::try_spawn_bomb(const math::Position2)
{
    const auto bombCanBeSpawned = can_spawn_bomb();
    if (bombCanBeSpawned)
    {
        launch_bomb();
    }
    return bombCanBeSpawned;
}

bool LimitedBombLauncher::can_spawn_bomb() const
{
    return max_bombs > bombs;
}

void LimitedBombLauncher::launch_bomb()
{
    ++bombs;
}

void LimitedBombLauncher::notify_exploded()
{
    if (can_retrieve_bomb())
    {
        retrieve_bomb();
    }
}

void LimitedBombLauncher::retrieve_bomb()
{
    --bombs;
}

bool LimitedBombLauncher::can_retrieve_bomb() const
{
    return bombs > 0;
}
