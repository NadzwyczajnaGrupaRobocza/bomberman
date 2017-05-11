#include "TimeBomb.hpp"

void TimeBomb::update(std::chrono::milliseconds dt)
{
    updateElapsedTime(dt);
    if (shouldExplode())
    {
        markExploded();
    }
}

void TimeBomb::updateElapsedTime(std::chrono::milliseconds dt )
{
    timeElapsed += dt;
}

bool TimeBomb::shouldExplode() const
{
    return timeElapsed >= bombTimer;
}

void TimeBomb::markExploded()
{
    exploded = true;
}

bool TimeBomb::areYouDead() const
{
    return false;
}

bool TimeBomb::hasExploded() const
{
    return exploded;
}
