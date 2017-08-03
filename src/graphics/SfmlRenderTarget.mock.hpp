#pragma once

#include <gmock/gmock.h>

#include "SfmlRenderTarget.hpp"

namespace graphics
{
class SfmlRenderTargetMock : public SfmlRenderTarget
{
public:
    using SfmlRenderTarget::SfmlRenderTarget;

    MOCK_METHOD0(initialize, void());
    MOCK_METHOD1(setSize, void(const sf::Vector2u));
    MOCK_CONST_METHOD0(getSize, sf::Vector2u());
    MOCK_METHOD1(activate, bool(bool));
};
}
