#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "math/Size.hpp"

namespace graphics
{
class SfmlRenderTarget : public sf::RenderTarget
{
public:
    SfmlRenderTarget(const sf::Vector2u size);

    using sf::RenderTarget::initialize;

    void setSize(const sf::Vector2u new_size);
    sf::Vector2u getSize() const override;
    bool activate(/*[[maybe_unused]]*/
                  const bool) override;

private:
    sf::Vector2u window_size;
};
}
