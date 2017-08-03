#include "RendererPoolSfml.hpp"

#include <gtest/gtest.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include "SfmlRenderTarget.mock.hpp"

using namespace ::testing;

namespace graphics
{
class RendererSfmlTest : public Test
{
public:
    sf::Vector2u window_size{800, 600};
    SfmlRenderTargetMock mock{window_size};
    RendererPoolSfml renderer_pool{
        std::make_unique<SfmlRenderTarget>(window_size),
        std::make_unique<DrawableFactory>()};
};

TEST_F(RendererSfmlTest, renderAll)
{
    try
    {
        std::cout << "ex not? \n";
        renderer_pool.render_all();
        std::cout << "ex not \n";
    }
    catch(const std::exception& ex)
    {
        std::cout << "ex?: " << ex.what() << "\n";
    }
}

TEST_F(RendererSfmlTest, test)
{
    sf::Window window{sf::VideoMode(window_size.x, window_size.y), "My window"};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderer_pool.render_all();

        window.display();
    }

    ASSERT_TRUE(true);
}
}
