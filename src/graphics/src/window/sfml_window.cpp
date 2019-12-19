#include "sfml_window.hpp"

#include <iostream>
#include <utility>

#include <boost/optional/optional.hpp>

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

auto sfml_window::is_open() const -> bool
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
            (*callback)(window_event{screen_event::Close});
            m_window->close();
        }
        else if (event.type == sf::Event::Resized && change_observer)
        {
            (*callback)(window_event{screen_event::Resize});
            change_observer->window_size_changed(get_window_size());
        }
        else if (event.type == sf::Event::Resized)
        {
            (*callback)(window_event{screen_event::Resize});
        }
    }
}

auto sfml_window::get_window_size() const -> window_size
{
    return m_window->get_window_size();
}

void sfml_window::subscribe(window_event_callback subscriber)
{
    callback = subscriber;
}
}
