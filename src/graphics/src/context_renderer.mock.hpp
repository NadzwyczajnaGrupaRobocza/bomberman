#pragma once

#include <gmock/gmock.h>

#include "context_renderer.hpp"

namespace graphics
{
class mock_context_renderer : public context_renderer
{
public:
    MOCK_METHOD0(initialize, void());
    MOCK_METHOD1(clear, void(const sf::Color&));
    MOCK_METHOD1(draw, void(const sfml_rectangle_shape&));
    MOCK_METHOD0(set_view, void());
    MOCK_METHOD1(set_view_size, void(const window_size&));
};
}
