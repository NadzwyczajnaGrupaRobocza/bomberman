#pragma once

#include "graphics/Window.hpp"

#include <SFML/Window/Window.hpp>

#include "WindowSize.hpp"

namespace graphics
{
class WindowSfml : public Window
{
public:
    WindowSfml(const WindowSize&);
    bool is_open() const override;
    void display() override;
    void update() override;

private:
    sf::Window window;
};
}
