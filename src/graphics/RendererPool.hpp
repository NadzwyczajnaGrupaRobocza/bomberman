#pragma once

#include "RenderId.hpp"
#include "math/Position.hpp"
#include "math/Size.hpp"

namespace graphics
{
class RendererPool
{
public:
    virtual ~RendererPool() = default;

    virtual RenderId take(const math::Size& size,
                          const math::Position2& position) = 0;
    virtual void give_back(const RenderId&) = 0;
    virtual void set_position(const RenderId&,
                              const math::Position2& position) = 0;
    virtual void render_all() = 0;
};
}
