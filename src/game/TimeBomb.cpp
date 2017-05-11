#include "TimeBomb.hpp"

void TimeBomb::update(std::chrono::milliseconds dt)
{
    timeElapsed += dt;
    if (timeElapsed >= bombTimer)
    {
        exploded = true;
    }
}

bool TimeBomb::areYouDead() const
{
    return false;
}

bool TimeBomb::hasExploded() const
{
    return exploded;
}
