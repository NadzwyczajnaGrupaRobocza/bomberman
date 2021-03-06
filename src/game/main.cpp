#include <chrono>
#include <memory>

#include "BombermanGameWorld.hpp"
#include "FieldSize.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "editor/HotReload.hpp"
#include "graphics/factory.hpp"
#include "math/Size2u.hpp"
#include "physics/ConcretePhysicsEngine.hpp"
#include "physics/PhysicsEngine.hpp"

int main()
{
    const auto hot_reload = editor::create_hot_reload();

    const math::Size2u initial_window_size{800, 800};
    const math::Size2u map_size{15, 15};

    auto p = std::make_unique<physics::ConcretePhysicsEngine>();
    auto r = graphics::create_renderer_pool(initial_window_size,
                                            scale_to_field_size(map_size));
    BombermanGameWorld world(std::move(p), std::move(r), map_size);
    auto window =
        graphics::create_window(initial_window_size, "Bomberman Remake", world);

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
