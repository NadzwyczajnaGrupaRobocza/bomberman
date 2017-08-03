#include "GameWorld.hpp"


bool BombermanGameWorld::is_bomb_at_pos(const BombPosition&) const
{
    return true;
}

std::unique_ptr<Bomb> BombermanGameWorld::create_bomb(const BombPosition&, const TimeToExplode) const
{

    return nullptr;
}

std::unique_ptr<Explosion> BombermanGameWorld::create_explosion(const ExplosionPosition&) const
{

    return nullptr;
}

void BombermanGameWorld::update(ElapsedTime)
{

    return;
}


