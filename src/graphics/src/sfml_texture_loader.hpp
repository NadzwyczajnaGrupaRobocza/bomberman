#pragma once

#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
using texture_path = std::string;

class sfml_texture_loader
{
public:
    virtual ~sfml_texture_loader() = default;

    virtual bool load(sf::Texture&, const texture_path&) = 0;
};
}
