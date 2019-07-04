#include "sfml_window.hpp"

#include <iostream>

namespace graphics
{
sfml_window::sfml_window(const window_size& size, const std::string& title,
                         std::unique_ptr<window_proxy> w)
    : m_window{std::move(w)}
{
    m_window->create(sf::VideoMode{size.width, size.height}, title);
}

bool sfml_window::is_open() const
{
    return m_window->is_open();
}

void sfml_window::display()
{
    m_window->display();
}

void sfml_window::update()
{
    sf::Event event;
    while (m_window->poll_event(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
    }
}

window_size get_window_size() const
{
    m_window->get_window_size();
}

}
