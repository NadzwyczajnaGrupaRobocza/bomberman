#pragma once

#include "Entity.hpp"

#include <memory>

#include "physics/PhysicsId.hpp"
#include "physics/PhysicsEngine.hpp"
#include "graphics/renderer_id.hpp"
#include "graphics/renderer_pool.hpp"
#include "BombLauncher.hpp"
#include "HumanPlayer.hpp"

class Bomberman : public Entity
{
public:
    explicit Bomberman(physics::PhysicsId, graphics::renderer_id,
                       std::unique_ptr<HumanPlayer>,
                       std::shared_ptr<physics::PhysicsEngine>,
                       std::shared_ptr<graphics::renderer_pool>,
                       std::shared_ptr<BombLauncher>);

    void update(DeltaTime) override;
    bool areYouDead() const override;

private:
    physics::PhysicsId physics_id;
    graphics::renderer_id renderer_id;
    std::unique_ptr<HumanPlayer> input;
    std::shared_ptr<BombLauncher> bomb_launcher;
    std::shared_ptr<physics::PhysicsEngine> physics_engine;
    std::shared_ptr<graphics::renderer_pool> renderer_pool;
};
