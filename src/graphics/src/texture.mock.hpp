#pragma once

#include <gmock/gmock.h>

#include "texture.hpp"

namespace graphics
{
class mock_texture
{
public:
    MOCK_METHOD1(load, bool(const texture_path&));
};
}
