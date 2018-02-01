#pragma once

#include <memory>

#include "BombLauncher.hpp"

class GameWorld;

class LimitedBombLauncher : public  BombLauncher
{
public:
    LimitedBombLauncher(std::shared_ptr<GameWorld>, int);

    bool try_spawn_bomb(const math::Position2) override;
    void notify_exploded() override;

private:
    std::shared_ptr<GameWorld> game_world;
    const int max_bombs;
    int bombs{0};

    bool can_spawn_bomb(math::Position2) const;
    void launch_bomb();
    bool can_retrieve_bomb() const;
    void retrieve_bomb();
};
