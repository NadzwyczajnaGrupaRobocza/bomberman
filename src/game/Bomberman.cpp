#include "Bomberman.hpp"

Bomberman::Bomberman(physics::PhysicsId phys_id, graphics::RendererId rend_id,
                     std::unique_ptr<HumanPlayer> player,
                     std::shared_ptr<physics::PhysicsEngine> physics,
                     std::shared_ptr<graphics::RendererPool> pool)
    : physics_id{phys_id}, renderer_id{rend_id}, input{std::move(player)},
      physics_engine{physics}, renderer_pool{pool}
{
}

void Bomberman::update(DeltaTime)
{
}

bool Bomberman::areYouDead() const
{
    return true;
}
