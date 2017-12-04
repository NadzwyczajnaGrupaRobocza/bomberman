#pragma once

#include <gmock/gmock.h>

#include "RenderTarget.hpp"

namespace graphics
{
class RenderTargetMock : public RenderTarget
{
public:
    MOCK_METHOD0(initialize, void());
    MOCK_METHOD1(clear, void(const sf::Color));
    MOCK_METHOD1(draw, void(const sf::Drawable&));
    MOCK_METHOD1(setSize, void(const sf::Vector2u));
    MOCK_CONST_METHOD0(getSize, sf::Vector2u());
};
}
