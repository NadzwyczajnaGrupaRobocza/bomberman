#include "TimeBomb.hpp"

TimeBomb::TimeBomb(physics::PhysicsEngine& pe, graphics::RendererPool& rp,
                   math::Position2f bomb_position,
                   std::shared_ptr<BombLauncher> bl)
    : physics_engine{pe}, renderer_pool{rp}, bombLauncher{std::move(bl)}
{
    physics_engine.register_colider(bomb_size, bomb_position);
    renderer_pool.acquire(bomb_size, bomb_position);
}

void TimeBomb::update(DeltaTime dt)
{
    updateElapsedTime(dt);
    if (shouldExplode())
    {
        explode();
    }
}

void TimeBomb::updateElapsedTime(DeltaTime dt)
{
    timeElapsed += std::chrono::duration_cast<std::chrono::milliseconds>(dt);
}

bool TimeBomb::shouldExplode() const
{
    return timeElapsed >= bombTimer;
}

void TimeBomb::explode()
{
    bombLauncher->notify_exploded();
    markExploded();
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
