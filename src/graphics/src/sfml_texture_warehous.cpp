#include "sfml_texture_warehous.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
sfml_texture_warehous::sfml_texture_warehous(
    std::unique_ptr<sfml_texture_loader> l)
    : loader{std::move(l)}
{
}

sf::Texture& sfml_texture_warehous::get_access(const texture_path& path)
{
    if (auto is_texture_not_loaded = allocate_texture_key(path))
    {
        load_texture(path);
    }
    return *textures[path];
}

bool sfml_texture_warehous::allocate_texture_key(const texture_path& path)
{
    return textures[path] == nullptr;
}

void sfml_texture_warehous::load_texture(const texture_path& path)
{
    if (auto tx = std::make_unique<sf::Texture>(); !loader->load(*tx, path))
    {
        throw sfml_texture_warehous::cannot_access{"cannot load: " + path};
    }
    else
    {
        textures[path] = std::move(tx);
    }
}

}
