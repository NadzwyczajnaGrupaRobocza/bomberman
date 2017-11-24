#pragma once

#include "graphics/Window.hpp"

#include <memory>
#include <SFML/Window/Window.hpp>

#include "WindowSize.hpp"
#include "SfmlWindow.hpp"

namespace graphics
{
class WindowSfml : public Window
{
public:
    WindowSfml(const WindowSize&, std::unique_ptr<SfmlWindow>);
    bool is_open() const override;
    void display() override;
    void update() override;

private:
    std::unique_ptr<SfmlWindow> window;
};
}
