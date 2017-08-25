#include <gtest/gtest.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "graphics/RendererPoolFactory.hpp"
#include "math/Size.hpp"
#include "math/Position.hpp"

int main()
{
    const math::Size window_size{800, 600};
    auto renderer_pool = graphics::RendererPoolFactory{}.create(window_size);

    sf::Window window(sf::VideoMode(static_cast<unsigned>(window_size.width),
                                    static_cast<unsigned>(window_size.height)),
                      "My window ");

    renderer_pool->take(math::Size{20.0f, 30.0f},
                        math::Position2{100.0f, 200.0f});

    renderer_pool->take(math::Size{30.0f, 30.0f},
                        math::Position2{200.0f, 350.0f});

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
