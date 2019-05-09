#include "BombermanGameWorld.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <chrono>

#include "math/Size2u.hpp"
#include "graphics/factory.hpp"
#include "physics/PhysicsEngine.hpp"
#include "physics/ConcretePhysicsEngine.hpp"

int main()
{
    const math::Size2u window_size{800, 600};

    auto window = graphics::create_window(window_size, "Bomberman Remake");
    auto r = graphics::create_renderer_pool(window_size);
    auto p = std::make_unique<physics::ConcretePhysicsEngine>();

    BombermanGameWorld world(std::move(p), std::move(r));
    auto last_frame{std::chrono::high_resolution_clock::now()};

    while (window->is_open())
    {
        auto const now = std::chrono::high_resolution_clock::now();

        world.update(DeltaTime{now - last_frame});
        window->update();
        window->display();

        last_frame = now;
    }
}

