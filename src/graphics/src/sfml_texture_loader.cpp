#include "sfml_texture_loader.hpp"

namespace graphics
{
namespace
{
auto create_texture(const texture_path& path)
{
    auto tx = std::make_unique<sf::Texture>();
    if (tx->loadFromFile(path))
    {
        return tx;
    }
    throw texture_load_error{"cannot load: " + path};
}
}
sf::Texture& sfml_texture_loader::load(const texture_path& path)
{
    if (textures[path] == nullptr)
    {
        textures[path] = create_texture(path);
    }

    return *textures[path];
}

}
