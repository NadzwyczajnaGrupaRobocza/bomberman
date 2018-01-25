#pragma once

#include "BombLauncher.hpp"

class LimitedBombLauncher : public  BombLauncher
{
public:
    LimitedBombLauncher(int);

    bool try_spawn_bomb(const math::Position2) override;
    void notifyExploded() override;

private:
    const int maxBombs;
    int bombs{0};

    bool canSpawnBomb() const;
    void launchBomb();
};
