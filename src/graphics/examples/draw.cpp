#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/factory.hpp"

class draw_app
{
public:
    draw_app()
    {
        shapes->acquire(math::Size2f{20, 30}, math::Position2f{100.0f, 200.0f},
                        graphics::color{255, 6, 112});
        shapes->acquire(math::Size2f{30, 30}, math::Position2f{200.0f, 350.0f},
                        graphics::color{8, 45, 89});
    }

    void run()
    {

        while (main_window->is_open())
        {
            display_frame();
        }
    }

private:
    void display_frame()
    {
        shapes->render_all();
        main_window->display();
        main_window->update();
    }

    math::Size2u const window_size{800, 600};
    std::unique_ptr<graphics::window> main_window{
        graphics::create_window(window_size, "My Window")};
    std::unique_ptr<graphics::renderer_pool> shapes{
        graphics::create_renderer_pool(window_size, {800, 600})};
};

int main()
{
    draw_app{}.run();
}
