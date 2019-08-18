#include "sfml_texture_loader.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
sfml_texture_loader::sfml_texture_loader(
    std::unique_ptr<sfml_texture_factory> factory)
    : texture_factory{std::move(factory)}
{
}

texture& sfml_texture_loader::load(const texture_path& path)
{
    if (auto is_texture_not_loaded = allocate_texture_key(path))
    {
        load_texture(path);
    }

    return *textures[path];
}

bool sfml_texture_loader::allocate_texture_key(const texture_path& path)
{
    return textures[path] == nullptr;
}

void sfml_texture_loader::load_texture(const texture_path& path)
{
    if (auto tx = texture_factory->create(); tx == nullptr or !tx->load(path))
    {
        throw texture_loader::load_error{"cannot load: " + path};
    }
    else
    {
        textures[path] = std::move(tx);
    }
}

}
