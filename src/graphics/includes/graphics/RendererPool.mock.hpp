#pragma once

#include "RendererPool.hpp"

namespace graphics
{
class MockRendererPool : public RendererPool
{
public:
    MOCK_METHOD2(acquire,
                 RendererId(const math::Size2f&, const math::Position2f&));
    MOCK_METHOD1(release, void(const RendererId&));
    MOCK_METHOD0(render_all, void());
    MOCK_METHOD2(set_position,
                 void(const RendererId&, const math::Position2f&));
    MOCK_METHOD1(get_position, math::Position2f(const RendererId&));
};
} // namespace graphics
