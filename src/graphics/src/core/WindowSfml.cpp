#include "WindowSfml.hpp"

#include <iostream>

namespace graphics
{
WindowSfml::WindowSfml(const WindowSize& size, std::unique_ptr<SfmlWindow> w)
    : window{std::move(w)}
{
    sf::String title("My Window");
    std::cout << "size: " << title.getSize()
              << "\ntitle: " << std::string(title) << '\n';
    window->create(sf::VideoMode{size.width, size.height}, title);
}

bool WindowSfml::is_open() const
{
    return window->is_open();
}

void WindowSfml::display()
{
    window->display();
}

void WindowSfml::update()
{
    sf::Event event;
    while (window->poll_event(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }
}
}
