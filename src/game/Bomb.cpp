#include "Bomb.hpp"

void Bomb::update(std::chrono::milliseconds)
{
}

bool Bomb::areYouDead() const
{
    return false;
}

bool Bomb::hasExploded() const
{
    return false;
}
