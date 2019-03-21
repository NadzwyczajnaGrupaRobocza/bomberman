#include "TimeBomb.hpp"

TimeBomb::TimeBomb(std::shared_ptr<physics::PhysicsEngine> pe,
                   std::shared_ptr<graphics::renderer_pool> rp,
                   math::Position2f bomb_position,
                   std::shared_ptr<BombLauncher> bl)
    : physics_engine{std::move(pe)}, renderer_pool{std::move(rp)},
      bombLauncher{std::move(bl)}, physics_id{physics_engine->register_colider(
                                       bomb_size, bomb_position)},
      renderer_id{renderer_pool->acquire(bomb_size, bomb_position,
                                         graphics::colors::red)}
{
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
    return !hasExploded() && timeElapsed >= bombTimer;
}

void TimeBomb::explode()
{
    bombLauncher->notify_exploded();
    deregister();
    markExploded();
}

void TimeBomb::deregister()
{
    physics_engine->deregister(physics_id);
    renderer_pool->release(renderer_id);
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
