#pragma once

#include "texture_loader.hpp"

namespace graphics
{
class mock_texture_loader : public texture_loader
{
public:
    MOCK_METHOD1(load, sf::Texture&(const texture_path&));
};
}
