#pragma once

#include <gmock/gmock.h>

#include "sfml_texture_factory.hpp"

namespace graphics
{
class mock_sfml_texture_factory : public sfml_texture_factory
{
public:
    MOCK_METHOD0(create, std::unique_ptr<sf::Texture>());
};
}
