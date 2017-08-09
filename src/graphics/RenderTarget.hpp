#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "ContextRenderer.hpp"

namespace graphics
{
class RenderTarget : public ContextRenderer, private sf::RenderTarget
{
public:
    RenderTarget(const sf::Vector2u size);

    void initialize() override;
    void clear(const sf::Color color) override;
    void draw(const SfmlRectangleShape&) override;

    void setSize(const sf::Vector2u new_size);

    sf::Vector2u getSize() const override;
    bool activate(/*[[maybe_unused]]*/
                  const bool) override;

private:
    sf::Vector2u window_size;
};
}
