#pragma once

#include <memory>
#include <unordered_map>

#include "texture_loader.hpp"

namespace graphics
{

class sfml_texture_loader : public texture_loader
{
public:
    sf::Texture& load(const texture_path&) override;

private:
    std::unordered_map<texture_path, std::unique_ptr<sf::Texture>> textures;
};
}
