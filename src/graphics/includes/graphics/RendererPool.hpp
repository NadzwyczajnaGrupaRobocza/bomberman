#pragma once

#include "RendererId.hpp"
#include "math/Position2f.hpp"
#include "math/Size2f.hpp"

namespace graphics
{
class RendererPool
{
public:
    virtual ~RendererPool() noexcept = default;

    virtual RendererId acquire(const math::Size2f&, const math::Position2f&) = 0;
    virtual void release(const RendererId&) = 0;

    //TODO: extract functions below to another abstraction
    virtual void render_all() = 0;
    virtual void set_position(const RendererId&, const math::Position2f&) = 0;
    virtual math::Position2f get_position(const RendererId&) = 0;
};
}
