#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <stdexcept>

namespace graphics
{
using texture_path = std::string;

struct texture_load_error : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class texture_loader
{
public:
    virtual ~texture_loader() = default;

    virtual sf::Texture& load(const texture_path&) = 0;
};
}
