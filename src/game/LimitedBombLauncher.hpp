#pragma once

#include "BombLauncher.hpp"

class LimitedBombLauncher : public  BombLauncher
{
public:
    LimitedBombLauncher(int);

    bool try_spawn_bomb(const math::Position2) override;
    void notify_exploded() override;

private:
    const int max_bombs;
    int bombs{0};

    bool can_spawn_bomb() const;
    void launch_bomb();
    bool can_retrieve_bomb() const;
    void retrieve_bomb();
};
