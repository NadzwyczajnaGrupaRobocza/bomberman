#include "sfml_texture_warehouse.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
sfml_texture_warehouse::sfml_texture_warehouse(
    std::unique_ptr<sfml_texture_loader> l)
    : loader{std::move(l)}
{
}

sf::Texture& sfml_texture_warehouse::get_access(const texture_path& path)
{
    constexpr auto texture_not_loaded{true};
    if (allocate_texture_key(path) == texture_not_loaded)
    {
        load_texture(path);
    }
    return *textures[path];
}

bool sfml_texture_warehouse::allocate_texture_key(const texture_path& path)
{
    return textures[path] == nullptr;
}

void sfml_texture_warehouse::load_texture(const texture_path& path)
{
    if (auto tx = std::make_unique<sf::Texture>(); !loader->load(*tx, path))
    {
        throw sfml_texture_warehouse::cannot_access{"cannot load: " + path};
    }
    else
    {
        textures[path] = std::move(tx);
    }
}

}
