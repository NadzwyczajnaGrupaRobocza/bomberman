#include "Bomb.hpp"

#include <memory>

#include "math/Position2f.hpp"
#include "math/Size2f.hpp"

#include "BombLauncher.hpp"
#include "graphics/renderer_pool.hpp"
#include "physics/PhysicsEngine.hpp"

class GameWorld;

class TimeBomb : public Bomb
{
public:
    TimeBomb(std::shared_ptr<physics::PhysicsEngine>,
             std::shared_ptr<graphics::renderer_pool>, math::Position2f,
             std::shared_ptr<BombLauncher>);

    void update(DeltaTime) override;
    bool areYouDead() const override;
    bool hasExploded() const override;

private:
    bool shouldExplode() const;
    void updateElapsedTime(DeltaTime);
    void explode();
    void markExploded();
    void deregister();

    const math::Size2f bomb_size{40.0, 40.0};
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
    std::shared_ptr<physics::PhysicsEngine> physics_engine;
    std::shared_ptr<graphics::renderer_pool> renderer_pool;
    const std::shared_ptr<BombLauncher> bombLauncher;
    physics::PhysicsId physics_id;
    graphics::renderer_id renderer_id;
    DeltaTime timeElapsed{};
};
