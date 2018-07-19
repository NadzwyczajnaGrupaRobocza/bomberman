#include "TimeBomb.hpp"

void TimeBomb::update(DeltaTime dt)
{
    updateElapsedTime(dt);
    if (shouldExplode())
    {
        markExploded();
    }
}

void TimeBomb::updateElapsedTime(DeltaTime dt )
{
    timeElapsed += std::chrono::duration_cast<std::chrono::milliseconds>(dt);
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
