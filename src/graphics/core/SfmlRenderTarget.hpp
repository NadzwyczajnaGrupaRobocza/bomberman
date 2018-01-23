#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "WindowSize.hpp"
#include "ContextRenderer.hpp"

namespace graphics
{
class SfmlRenderTarget : public ContextRenderer, private sf::RenderTarget
{
public:
    SfmlRenderTarget(const WindowSize& size);

    void initialize() override;
    void clear(const sf::Color& color) override;
    void draw(const SfmlRectangleShape&) override;

    sf::Vector2u getSize() const override;
    bool activate([[maybe_unused]] bool) override;

protected:
    WindowSize window_size;
};
}
