#pragma once

#include "sfml_texture_loader.hpp"

namespace graphics
{
class simple_sfml_texture_loader : public sfml_texture_loader
{
public:
    bool load(sf::Texture&, const texture_path&) override;
};
}
