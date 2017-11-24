#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "WindowSize.hpp"
#include "ContextRenderer.hpp"

namespace graphics
{
class RenderTarget : public ContextRenderer, private sf::RenderTarget
{
public:
    RenderTarget(const WindowSize& size);

    void initialize() override;
    void clear(const sf::Color& color) override;
    void draw(const SfmlRectangleShape&) override;

    void setSize(const WindowSize& new_size);

    sf::Vector2u getSize() const override;
    bool activate(/*[[maybe_unused]]*/
                  const bool) override;

protected:
    WindowSize window_size;
};
}
