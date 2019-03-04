#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace graphics
{
class sfml_window
{
public:
    virtual ~sfml_window() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual bool poll_event(sf::Event&) = 0;
    virtual void close() = 0;
    virtual void create(sf::VideoMode, const sf::String& title) = 0;
};
}
