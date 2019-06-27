#include "BombermanGameWorld.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "graphics/factory.hpp"
#include "math/Size2u.hpp"
#include "physics/ConcretePhysicsEngine.hpp"
#include "physics/PhysicsEngine.hpp"
#include <chrono>
#include <memory>

#include "editor/HotReload.hpp"

int main()
{
    const auto hot_reload = editor::create_hot_reload();

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

        hot_reload->update();
    }
}
