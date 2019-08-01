#pragma once

#include "texture_warehous.hpp"

namespace graphics
{
class mock_texture_warehous : public texture_warehous
{
public:
    MOCK_METHOD1(get_access, sf::Texture&(const texture_path&));
};
}
