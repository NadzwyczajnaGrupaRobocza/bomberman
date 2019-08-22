#include <boost/optional/optional.hpp>
#include <iostream>
#include <utility>

#include "sfml_window.hpp"

namespace graphics
{
sfml_window::sfml_window(const window_size& size, const std::string& title,
                         std::unique_ptr<window_proxy> w,
                         window_change_observer& observer)
    : sfml_window{size, title, std::move(w),
                  boost::optional<window_change_observer&>(observer)}
{
}

sfml_window::sfml_window(const window_size& size, const std::string& title,
                         std::unique_ptr<window_proxy> w)
    : sfml_window{size, title, std::move(w), boost::none}
{
}

sfml_window::sfml_window(const window_size& size, const std::string& title,
                         std::unique_ptr<window_proxy> w,
                         boost::optional<window_change_observer&> observer)
    : m_window{std::move(w)}, change_observer{observer}
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
        else if (event.type == sf::Event::Resized && change_observer)
        {
            change_observer->window_size_changed(get_window_size());
        }
    }
}

window_size sfml_window::get_window_size() const
{
    return m_window->get_window_size();
}

}
