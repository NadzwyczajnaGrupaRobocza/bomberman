#include "Bomb.hpp"

#include <memory>

#include "math/Size2f.hpp"
#include "math/Position2f.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/renderer_pool.hpp"
#include "BombLauncher.hpp"

class GameWorld;

class TimeBomb : public Bomb
{
public:
    TimeBomb(physics::PhysicsEngine&, graphics::renderer_pool&,
             math::Position2f, std::shared_ptr<BombLauncher>);

    void update(DeltaTime) override;
    bool areYouDead() const override;
    bool hasExploded() const override;

private:
    bool shouldExplode() const;
    void updateElapsedTime(DeltaTime);
    void explode();
    void markExploded();
    void deregister();

    const math::Size2f bomb_size{1.0, 1.0};
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
    physics::PhysicsEngine& physics_engine;
    graphics::renderer_pool& renderer_pool;
    const std::shared_ptr<BombLauncher> bombLauncher;
    physics::PhysicsId physics_id;
    graphics::renderer_id renderer_id;
    std::chrono::milliseconds timeElapsed{};
};
