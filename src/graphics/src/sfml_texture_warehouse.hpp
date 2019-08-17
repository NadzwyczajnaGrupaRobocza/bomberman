#pragma once

#include <memory>
#include <unordered_map>

#include "sfml_texture_loader.hpp"
#include "texture_warehouse.hpp"

namespace graphics
{

class sfml_texture_warehouse : public texture_warehouse
{
public:
    explicit sfml_texture_warehouse(std::unique_ptr<sfml_texture_loader>);

    sf::Texture& get_access(const texture_path&) override;

private:
    void load_texture(const texture_path&);
    bool allocate_texture_key(const texture_path&);

    std::unordered_map<texture_path, std::unique_ptr<sf::Texture>> textures;
    std::unique_ptr<sfml_texture_loader> loader;
};
}
