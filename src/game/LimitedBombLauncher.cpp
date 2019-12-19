#include "LimitedBombLauncher.hpp"

#include "GameWorld.hpp"

#include "Bomb.hpp"

LimitedBombLauncher::LimitedBombLauncher(std::shared_ptr<GameWorld> gw,
                                         std::shared_ptr<BombFactory> bf,
                                         const int maximum_bombs)
    : game_world{std::move(gw)}, bomb_factory{std::move(bf)}, max_bombs{
                                                                  maximum_bombs}
{
}

auto LimitedBombLauncher::try_spawn_bomb(const math::Position2f pos) -> bool
{
    const auto bombCanBeSpawned = can_spawn_bomb(pos);
    if (bombCanBeSpawned)
    {
        launch_bomb(pos);
    }
    return bombCanBeSpawned;
}

auto LimitedBombLauncher::can_spawn_bomb(const math::Position2f pos) const -> bool
{
    return max_bombs > bombs && !game_world->is_bomb_at_pos(BombPosition{pos});
}

void LimitedBombLauncher::launch_bomb(math::Position2f pos)
{
    ++bombs;
    auto bomb = bomb_factory->create_time_bomb(pos, shared_from_this());
    game_world->register_bomb(BombPosition{pos}, std::move(bomb));
}

void LimitedBombLauncher::notify_exploded()
{
    if (can_retrieve_bomb())
    {
        retrieve_bomb();
    }
}

auto LimitedBombLauncher::retrieve_bomb() -> void
{
    --bombs;
}

auto LimitedBombLauncher::can_retrieve_bomb() const -> bool
{
    return bombs > 0;
}
