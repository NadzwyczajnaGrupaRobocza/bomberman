#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/String.hpp>

namespace graphics
{
class SfmlWindow
{
public:
    virtual ~SfmlWindow() noexcept = default;

    virtual bool is_open() const = 0;
    virtual void display() = 0;
    virtual bool poll_event(sf::Event&) = 0;
    virtual void close() = 0;
    virtual void create(sf::VideoMode, const sf::String& title) = 0;
};
}
