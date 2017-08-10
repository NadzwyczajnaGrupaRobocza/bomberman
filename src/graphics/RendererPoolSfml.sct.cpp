#include <gtest/gtest.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>

#include "SfmlRectangleShape.hpp"
#include "RenderTarget.hpp"
#include "RendererIdGenerator.hpp"
#include "RendererPoolSfml.hpp"
#include "math/Size.hpp"
#include "math/Position.hpp"

namespace graphics
{
TEST(RendererPoolSfmlSct, runAndDraw)
{
    const sf::Vector2u window_size{800, 600};
    RendererPoolSfml renderer_pool(std::make_unique<RenderTarget>(window_size),
                                   std::make_unique<RendererIdGenerator>());

    sf::Window window(sf::VideoMode(window_size.x, window_size.y),
                      "My window ");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderer_pool.render_all();
        renderer_pool.take(math::Size{20.0f, 30.0f},
                           math::Position2{100.0f, 200.0f});

        window.display();
    }

    ASSERT_TRUE(true);
}
}
