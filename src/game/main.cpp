#include <chrono>
#include <memory>

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"

#include "BombermanGameWorld.hpp"
#include "FieldSize.hpp"
#include "graphics/factory.hpp"
#include "math/Size2u.hpp"
#include "physics/ConcretePhysicsEngine.hpp"
#include "physics/PhysicsEngine.hpp"

int main()
{
    const math::Size2u window_size{800, 600};
    const math::Size2u map_size{125, 100};

    auto window = graphics::create_window(window_size, "Bomberman Remake");
    auto r = graphics::create_renderer_pool(window_size,
                                            scale_to_field_size(map_size));
    auto p = std::make_unique<physics::ConcretePhysicsEngine>();

    BombermanGameWorld world(std::move(p), std::move(r), map_size);
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
