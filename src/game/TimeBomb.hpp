#include "Bomb.hpp"

#include "physics/PhysicsEngine.hpp"
#include "graphics/RendererPool.hpp"

class GameWorld;

class TimeBomb : public Bomb
{
public:
    TimeBomb() = default; // TODO: remove
    TimeBomb(const physics::PhysicsEngine&, const graphics::RendererPool&);

    void update(std::chrono::milliseconds) override;
    bool areYouDead() const override;
    bool hasExploded() const override;

private:
    bool exploded{false};
    const std::chrono::seconds bombTimer{3};
    std::chrono::milliseconds timeElapsed{};

    bool shouldExplode() const;
    void updateElapsedTime(std::chrono::milliseconds);
    void markExploded();
};
