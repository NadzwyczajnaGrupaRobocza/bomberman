#include "BombermanGameWorld.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "graphics/factory.hpp"
#include "math/Size2u.hpp"
#include "physics/ConcretePhysicsEngine.hpp"
#include "physics/PhysicsEngine.hpp"
#include <chrono>
#include <memory>

#include "jet/live/Live.hpp"

int main()
{
    auto hot_reload{std::make_shared<jet::Live>()};

    const math::Size2u window_size{800, 600};

    auto window = graphics::create_window(window_size, "Bomberman Remake");
    auto r = graphics::create_renderer_pool(window_size);
    auto p = std::make_unique<physics::ConcretePhysicsEngine>();

    BombermanGameWorld world(std::move(p), std::move(r));
    auto last_frame{std::chrono::high_resolution_clock::now()};

    bool reloading{false};
    while (window->is_open())
    {
        auto const now = std::chrono::high_resolution_clock::now();

        world.update(DeltaTime{now - last_frame});
        window->update();
        window->display();

        last_frame = now;

        hot_reload->update();
        if (not reloading && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            hot_reload->tryReload();
            reloading = true;
        }
        else if (not sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            reloading = false;
        }
    }
}
