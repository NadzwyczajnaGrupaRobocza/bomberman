#pragma once

#include <SFML/Window/Event.hpp>

class SfmlWindowEventObserver
{
public:
    virtual ~SfmlWindowEventObserver() = default;

    virtual void next_frame() = 0;
    virtual void update(sf::Event) = 0;
};
