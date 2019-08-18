#pragma once

#include "texture_warehouse.hpp"

namespace graphics
{
class mock_texture_warehouse : public texture_warehouse
{
public:
    MOCK_METHOD1(get_access, sf::Texture&(const texture_path&));
};
}
