#pragma once

#include "RenderId.hpp"
#include "math/Position.hpp"
#include "math/Size.hpp"

namespace graphics
{
class RenderEngine
{
public:
    virtual ~RenderEngine() = default;

    virtual RenderId register_renderable(const math::Size& size,
                                         const math::Position2& position) = 0;
    virtual void deregister(const RenderId&) = 0;
    virtual void set_position(const RenderId&,
                              const math::Position2& position) = 0;
    virtual void render() = 0;
};
}
