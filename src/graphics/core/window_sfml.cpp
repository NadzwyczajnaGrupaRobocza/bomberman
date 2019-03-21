#include "window_sfml.hpp"

#include <iostream>

namespace graphics
{
window_sfml::window_sfml(const window_size& size, const std::string& title,
                         std::unique_ptr<sfml_window> w)
    : window{std::move(w)}
{
    window->create(sf::VideoMode{size.width, size.height}, title);
}

bool window_sfml::is_open() const
{
    return window->is_open();
}

void window_sfml::display()
{
    window->display();
}

void window_sfml::update()
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
