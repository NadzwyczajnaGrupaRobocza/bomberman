#pragma once

#include "renderer_id.hpp"
#include "math/Position2f.hpp"
#include "math/Size2f.hpp"
#include "graphics/color.hpp"

namespace graphics
{
class renderer_pool
{
public:
    virtual ~renderer_pool() noexcept = default;

    virtual renderer_id acquire(const math::Size2f&, const math::Position2f&,
                                const color&) = 0;
    virtual void release(const renderer_id&) = 0;

    // TODO: extract functions below to another abstraction
    virtual void render_all() = 0;

    virtual void set_position(const renderer_id&, const math::Position2f&) = 0;
    virtual math::Position2f get_position(const renderer_id&) = 0;

    virtual void set_color(const renderer_id&, const color&) = 0;
    virtual color get_color(const renderer_id&) const = 0;
};
} // namespace graphics
