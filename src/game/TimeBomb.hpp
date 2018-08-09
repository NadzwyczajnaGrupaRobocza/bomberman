#include "Bomb.hpp"

#include <memory>

#include "math/Size2f.hpp"
#include "math/Position2f.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"
#include "BombLauncher.hpp"

class GameWorld;

class TimeBomb : public Bomb
{
public:
    TimeBomb(physics::PhysicsEngine&, graphics::RendererPool&,
             math::Position2f, std::shared_ptr<BombLauncher>);

    void update(DeltaTime) override;
    bool areYouDead() const override;
    bool hasExploded() const override;

private:
    physics::PhysicsEngine& physics_engine;
    graphics::RendererPool& renderer_pool;
    const std::shared_ptr<BombLauncher> bombLauncher;
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
    std::chrono::milliseconds timeElapsed{};
    const math::Size2f bomb_size{1.0, 1.0};

    bool shouldExplode() const;
    void updateElapsedTime(DeltaTime);
    void markExploded();
};
