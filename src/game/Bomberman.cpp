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
    auto position = physics_engine->get_position(physics_id);
    renderer_pool->set_position(renderer_id, position);

    const auto new_direction = input->get_direction();
    position.x += new_direction.x;
    position.y += new_direction.y;

    physics_engine->set_position(physics_id, position);
}

bool Bomberman::areYouDead() const
{
    return true;
}
