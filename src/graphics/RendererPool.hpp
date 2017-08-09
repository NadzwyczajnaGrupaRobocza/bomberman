#pragma once

#include "RendererId.hpp"
#include "math/Position.hpp"
#include "math/Size.hpp"

namespace graphics
{
class RendererPool
{
public:
    virtual ~RendererPool() = default;

    virtual RendererId take(const math::Size& size,
                            const math::Position2& position) = 0;
    virtual void give_back(const RendererId&) = 0;
    virtual void cleanup_unused() = 0;
    virtual void render_all() = 0;

    virtual void set_position(const RendererId&,
                              const math::Position2& position) = 0;
};
}
