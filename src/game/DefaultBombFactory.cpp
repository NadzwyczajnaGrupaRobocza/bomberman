#include "DefaultBombFactory.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/renderer_pool.hpp"

#include "TimeBomb.hpp"

DefautlBombFactory::DefautlBombFactory(physics::PhysicsEngine& pe,
                                       graphics::renderer_pool& rp)
    : physics_engine{pe}, renderer_pool{rp}
{
}

std::unique_ptr<Bomb> DefautlBombFactory::create_time_bomb(
    math::Position2f bomb_position,
    std::shared_ptr<BombLauncher> bombLauncher) const
{
    return std::make_unique<TimeBomb>(physics_engine, renderer_pool,
                                      bomb_position, std::move(bombLauncher));
}
