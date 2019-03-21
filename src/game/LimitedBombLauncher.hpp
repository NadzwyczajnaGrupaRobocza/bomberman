#pragma once

#include <memory>

#include "BombFactory.hpp"

#include "BombLauncher.hpp"

class GameWorld;

class LimitedBombLauncher
    : public BombLauncher,
      public std::enable_shared_from_this<LimitedBombLauncher>
{
public:
    LimitedBombLauncher(std::shared_ptr<GameWorld>,
                        std::shared_ptr<BombFactory>, int);

    bool try_spawn_bomb(math::Position2f) override;
    void notify_exploded() override;

private:
    std::shared_ptr<GameWorld> game_world;
    std::shared_ptr<BombFactory> bomb_factory;
    const int max_bombs;
    int bombs{0};

    bool can_spawn_bomb(math::Position2f) const;
    void launch_bomb(math::Position2f);
    bool can_retrieve_bomb() const;
    void retrieve_bomb();
};
