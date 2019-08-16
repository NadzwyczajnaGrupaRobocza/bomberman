#include "sfml_window_proxy.hpp"

namespace graphics
{
sfml_window_proxy::sfml_window_proxy(const window_size&, const std::string&)
{
}

bool sfml_window_proxy::is_open() const
{
    return m_window.isOpen();
}

void sfml_window_proxy::display()
{
    m_window.display();
}

bool sfml_window_proxy::poll_event(sf::Event& event)
{
    return m_window.pollEvent(event);
}

void sfml_window_proxy::close()
{
    return m_window.close();
}

void sfml_window_proxy::create(sf::VideoMode mode, const sf::String& title)
{
    return m_window.create(mode, title);
}

window_size sfml_window_proxy::get_window_size() const
{
    return m_window.getSize();
}

}
