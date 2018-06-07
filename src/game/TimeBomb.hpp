#include "Bomb.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"

class GameWorld;

class TimeBomb : public Bomb
{
public:
    TimeBomb(physics::PhysicsEngine&, graphics::RendererPool&);

    void update(std::chrono::milliseconds) override;
    bool areYouDead() const override;
    bool hasExploded() const override;

private:
    physics::PhysicsEngine& physics_engine;
    graphics::RendererPool& renderer_pool;
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
    std::chrono::milliseconds timeElapsed{};

    bool shouldExplode() const;
    void updateElapsedTime(std::chrono::milliseconds);
    void markExploded();
};
