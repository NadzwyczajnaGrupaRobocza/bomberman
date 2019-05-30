#pragma once

#include "gmock/gmock.h"

#include "renderer_pool.hpp"

namespace graphics
{
class mock_renderer_pool : public renderer_pool
{
public:
    MOCK_METHOD3(acquire, renderer_id(const math::Size2f&,
                                      const math::Position2f&, const color&));
    MOCK_METHOD1(release, void(const renderer_id&));
    MOCK_METHOD0(render_all, void());
    MOCK_METHOD2(set_position,
                 void(const renderer_id&, const math::Position2f&));
    MOCK_METHOD1(get_position, math::Position2f(const renderer_id&));
    MOCK_METHOD2(set_color, void(const renderer_id&, const color&));
    MOCK_CONST_METHOD1(get_color, color(const renderer_id&));
    MOCK_METHOD2(set_texture, void(const renderer_id&, const std::string&));
};
}
