#include <gtest/gtest.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/RendererPoolFactory.hpp"
#include "graphics/Size.hpp"
#include "graphics/WindowSize.hpp"
#include "graphics/Position.hpp"

int main()
{
    const graphics::WindowSize window_size{800, 600};
    auto renderer_pool = graphics::RendererPoolFactory{}.create(window_size);

    sf::Window window(sf::VideoMode(window_size.width, window_size.height),
                      "My window ");

    renderer_pool->take(graphics::Size{20, 30}, graphics::Position{100, 200});
    renderer_pool->take(graphics::Size{30, 30}, graphics::Position{200, 350});

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
