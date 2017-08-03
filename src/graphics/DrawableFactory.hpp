#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "SfmlRectangleShape.hpp"

namespace graphics
{
class DrawableFactory
{
public:
    virtual ~DrawableFactory() = default;
    std::unique_ptr<SfmlRectangleShape>
    create_rectangle(const sf::Vector2f size) const;
};
}
