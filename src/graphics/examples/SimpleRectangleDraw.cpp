#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/RendererPoolFactory.hpp"

using namespace math;

int main()
{
    const Size2u window_size{800, 600};
    auto renderer_pool = graphics::create_renderer_pool(window_size);
    auto window = graphics::create_window(window_size, "My Window");

    renderer_pool->take(Size2f{20, 30}, Position2f{100.0f, 200.0f});
    renderer_pool->take(Size2f{30, 30}, Position2f{200.0f, 350.0f});

    while (window->is_open())
    {
        renderer_pool->render_all();
        window->display();
        window->update();
    }
}
