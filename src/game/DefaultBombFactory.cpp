#include "DefaultBombFactory.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/renderer_pool.hpp"

#include "TimeBomb.hpp"

DefautlBombFactory::DefautlBombFactory(
    std::shared_ptr<physics::PhysicsEngine> pe,
    std::shared_ptr<graphics::renderer_pool> rp)
    : physics_engine{std::move(pe)}, renderer_pool{std::move(rp)}
{
}

std::unique_ptr<Bomb> DefautlBombFactory::create_time_bomb(
    math::Position2f bomb_position,
    std::shared_ptr<BombLauncher> bombLauncher) const
{
    return std::make_unique<TimeBomb>(physics_engine, renderer_pool,
                                      bomb_position, std::move(bombLauncher));
}
