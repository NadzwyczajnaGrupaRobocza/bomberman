#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/RendererPoolFactory.hpp"

using namespace math;

int main()
{
    const Size2u window_size{800, 600};
    auto renderer_pool = graphics::RendererPoolFactory{}.create(window_size);

    sf::Window window(sf::VideoMode(window_size.width, window_size.height),
                      "My window ");

    renderer_pool->take(Size2f{20, 30}, Position2f{100, 200});
    renderer_pool->take(Size2f{30, 30}, Position2f{200, 350});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderer_pool->render_all();
        window.display();
    }
}
