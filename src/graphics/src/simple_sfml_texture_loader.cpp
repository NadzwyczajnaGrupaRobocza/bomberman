#include "simple_sfml_texture_loader.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
bool simple_sfml_texture_loader::load(sf::Texture& texture,
                                      const texture_path& path)
{
    return texture.loadFromFile(path);
}

}
