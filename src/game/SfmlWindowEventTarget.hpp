#pragma once

#include <SFML/Window/Event.hpp>

class SfmlWindowEventTarget
{
public:
    virtual ~SfmlWindowEventTarget() = default;

    virtual void on_event(sf::Event) = 0;
};
