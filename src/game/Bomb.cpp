#include "Bomb.hpp"

void Bomb::update(std::chrono::milliseconds dt)
{
    using namespace std::chrono_literals;
    if (dt > 3s)
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
