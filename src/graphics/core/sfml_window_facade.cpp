#include "sfml_window_facade.hpp"

namespace graphics
{
sfml_window_facade::sfml_window_facade(const window_size&, const std::string&)
{
}

bool sfml_window_facade::is_open() const
{
    return window.isOpen();
}

void sfml_window_facade::display()
{
    window.display();
}

bool sfml_window_facade::poll_event(sf::Event& event)
{
    return window.pollEvent(event);
}

void sfml_window_facade::close()
{
    return window.close();
}

void sfml_window_facade::create(sf::VideoMode mode, const sf::String& title)
{
    return window.create(mode, title);
}
}
