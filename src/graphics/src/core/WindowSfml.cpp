#include "WindowSfml.hpp"

#include <SFML/Window/Event.hpp>

namespace graphics
{
WindowSfml::WindowSfml(const WindowSize& size)
    : window{sf::VideoMode{size}, "My Window"}
{
}

bool WindowSfml::is_open() const
{
    return window.isOpen();
}

void WindowSfml::display()
{
    window.display();
}

void WindowSfml::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}
}
