#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/factory.hpp"

inline namespace variables
{
auto const window_size = math::Size2u{800, 600};
auto window = graphics::create_window(window_size, "My Window");
auto renderer_pool = graphics::create_renderer_pool(window_size);
auto first_box_id = renderer_pool -> acquire(math::Size2f{20, 30},
                                             math::Position2f{100.0f, 200.0f},
                                             graphics::color{255, 6, 112});
auto second_box_id = renderer_pool -> acquire(math::Size2f{30, 30},
                                              math::Position2f{200.0f, 350.0f},
                                              graphics::color{8, 45, 89});
} // namespace variables

inline namespace functions
{
inline auto display_frame()
{
    renderer_pool->render_all();
    window->display();
    window->update();
}
} // namespace functions

int main()
{
    while (window->is_open())
    {
        display_frame();
    }
}
