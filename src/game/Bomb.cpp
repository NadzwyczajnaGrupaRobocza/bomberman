#include "Bomb.hpp"

void Bomb::update(std::chrono::milliseconds dt)
{
    if (dt >= bombTimer)
    {
        exploded = true;
    }
}

bool Bomb::areYouDead() const
{
    return false;
}

bool Bomb::hasExploded() const
{
    return exploded;
}
