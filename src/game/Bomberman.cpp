#include "Bomberman.hpp"

Bomberman::Bomberman(physics::PhysicsId phys_id, graphics::renderer_id rend_id,
                     std::unique_ptr<HumanPlayer> player,
                     std::shared_ptr<physics::PhysicsEngine> physics,
                     std::shared_ptr<graphics::renderer_pool> pool,
                     std::unique_ptr<BombLauncher> launcher)
    : physics_id{phys_id}, renderer_id{rend_id}, input{std::move(player)},
      bomb_launcher{std::move(launcher)}, physics_engine{physics},
      renderer_pool{pool}
{
}

void Bomberman::update(DeltaTime dt)
{
    constexpr float speedup_factor{100};
    auto position = physics_engine->get_position(physics_id);
    renderer_pool->set_position(renderer_id, position);

    if (input->wants_bomb())
    {
        bomb_launcher->try_spawn_bomb(position);
    }

    const auto new_direction = input->get_direction();
    position.x += (speedup_factor * new_direction.x) * dt.count();
    position.y += (speedup_factor * new_direction.y) * dt.count();

    physics_engine->set_position(physics_id, position);
}

bool Bomberman::areYouDead() const
{
    return false;
}
