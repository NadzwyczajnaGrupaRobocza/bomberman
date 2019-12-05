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

struct temporary_observer : graphics::window_change_observer
{
    temporary_observer(std::shared_ptr<graphics::renderer_pool> r) : rpool{r}
    {
    }

    // void notify(internal_event)
    // {
    //     rpool->set_rendering_size(size);
    // }

    void window_size_changed(const graphics::window_size& size)
    {
        // rpool->set_rendering_size(size);
    }

    std::shared_ptr<graphics::renderer_pool> rpool;
};

int main()
{
    const auto hot_reload = editor::create_hot_reload();

    const math::Size2u initial_window_size{800, 800};
    const math::Size2u map_size{15, 15};

    auto p = std::make_unique<physics::ConcretePhysicsEngine>();
    std::shared_ptr<graphics::renderer_pool> r = graphics::create_renderer_pool(
        initial_window_size, scale_to_field_size(map_size));

    BombermanGameWorld world(std::move(p), r, map_size);

    auto window_size_changer = temporary_observer{r};
    auto window = graphics::create_window(
        initial_window_size, "Bomberman Remake", window_size_changer);

    window.subscribe([r](const auto& window_event)
                     {
                         r->set_rendering_size(size);
                     });

    auto last_frame{std::chrono::high_resolution_clock::now()};

    while (window->is_open())
    {
        auto const now = std::chrono::high_resolution_clock::now();

        window->update();
        world.update(DeltaTime{now - last_frame});
        window->display();

        last_frame = now;

        hot_reload->update();
    }
}
