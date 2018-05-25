#pragma once

#include "Entity.hpp"

#include <memory>

#include "physics/PhysicsId.hpp"
#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererId.hpp"
#include "graphics/RendererPool.hpp"
#include "BombLauncher.hpp"
#include "HumanPlayer.hpp"

class Bomberman : public Entity
{
public:
    explicit Bomberman(physics::PhysicsId, graphics::RendererId,
                       std::unique_ptr<HumanPlayer>,
                       std::shared_ptr<physics::PhysicsEngine>,
                       std::shared_ptr<graphics::RendererPool>,
                       std::unique_ptr<BombLauncher>);

    void update(DeltaTime) override;
    bool areYouDead() const override;

private:
    physics::PhysicsId physics_id;
    graphics::RendererId renderer_id;
    std::unique_ptr<HumanPlayer> input;
    std::shared_ptr<physics::PhysicsEngine> physics_engine;
    std::shared_ptr<graphics::RendererPool> renderer_pool;
    std::unique_ptr<BombLauncher> bomb_launcher;
};
