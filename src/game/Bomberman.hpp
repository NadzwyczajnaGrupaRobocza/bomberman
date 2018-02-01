#pragma once

#include "Entity.hpp"

#include <memory>

#include "physics/PhysicsId.hpp"
#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererId.hpp"
#include "graphics/RendererPool.hpp"
#include "HumanPlayer.hpp"

class Bomberman : public Entity
{
public:
    void update(DeltaTime) override;
    bool areYouDead() const override;

private:
    physics::PhysicsId physicsId;
    std::shared_ptr<physics::PhysicsEngine> physicsEngine;

    graphics::RendererId rendererId;
    std::shared_ptr<graphics::RendererPool> rendererPool;

    std::unique_ptr<HumanPlayer> input;
};
