#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace graphics
{
class sfml_texture_factory
{
public:
    virtual ~sfml_texture_factory() = default;

    virtual std::unique_ptr<sf::Texture> create()
    {
        return std::make_unique<sf::Texture>();
    }
};
}
