#pragma once

#include "RendererId.hpp"
#include "Position.hpp"
#include "Size.hpp"

namespace graphics
{
class RendererPool
{
public:
    virtual ~RendererPool() noexcept = default;

    virtual RendererId take(const Size&, const Position&) = 0;
    virtual void give_back(const RendererId&) = 0;
    virtual void render_all() = 0;
    virtual void set_position(const RendererId&, const Position&) = 0;
    virtual Position get_position(const RendererId&) = 0;
};
}
