#include "DefaultBombFactory.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"

#include "TimeBomb.hpp"

DefautlBombFactory::DefautlBombFactory(const physics::PhysicsEngine& pe,
                                       const graphics::RendererPool& rp)
    : physics_engine{pe}, renderer_pool{rp}
{
}

std::unique_ptr<Bomb> DefautlBombFactory::create_time_bomb() const
{
    return std::make_unique<TimeBomb>(physics_engine, renderer_pool);
}
