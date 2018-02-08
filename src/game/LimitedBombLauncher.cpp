#include "LimitedBombLauncher.hpp"

#include "GameWorld.hpp"

LimitedBombLauncher::LimitedBombLauncher(std::shared_ptr<GameWorld> gw,
                                         std::shared_ptr<BombFactory> bf,
                                         const int maximum_bombs)
    : game_world{std::move(gw)}, bomb_factory{std::move(bf)}, max_bombs{maximum_bombs}
{
}

bool LimitedBombLauncher::try_spawn_bomb(const math::Position2f pos)
{
    const auto bombCanBeSpawned = can_spawn_bomb(pos);
    if (bombCanBeSpawned)
    {
        launch_bomb();
    }
    return bombCanBeSpawned;
}

bool LimitedBombLauncher::can_spawn_bomb(const math::Position2f pos) const
{
    return max_bombs > bombs && !game_world->is_bomb_at_pos(BombPosition{pos});
}

void LimitedBombLauncher::launch_bomb()
{
    ++bombs;
    bomb_factory->create_time_bomb();
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
