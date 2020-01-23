#include "sfml_window.hpp"

#include <iostream>
#include <utility>

#include <boost/optional/optional.hpp>

#include "graphics/window_event.hpp"

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

auto to_internal(const sf::Event external_event) -> window_event
{
    switch (external_event.type)
    {
    case sf::Event::Closed: return {screen_event::Close};
    case sf::Event::Resized: return {screen_event::Resize};
    default: return {};
    }
}

void sfml_window::update()
{
    sf::Event event;
    while (m_window->poll_event(event))
    {
        if (callback)
        {

            (*callback)(to_internal(event));
        }
    }
}

auto sfml_window::close() -> void
{
    m_window->close();
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
