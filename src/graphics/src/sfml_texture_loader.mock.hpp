#pragma once

#include <gmock/gmock.h>

#include "sfml_texture_loader.hpp"

namespace graphics
{
class mock_sfml_texture_loader : public sfml_texture_loader
{
public:
    virtual ~mock_sfml_texture_loader() = default;

    MOCK_METHOD2(load, bool(sf::Texture&, const texture_path&));
};
}
