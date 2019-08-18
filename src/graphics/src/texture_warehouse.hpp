#pragma once

#include <stdexcept>
#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace graphics
{
using texture_path = std::string;

class texture_warehouse
{
public:
    struct cannot_access : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    virtual ~texture_warehouse() = default;
    virtual sf::Texture& get_access(const texture_path&) = 0;
};
}
