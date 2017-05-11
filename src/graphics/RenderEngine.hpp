#pragma once

#include <glm/fwd.hpp>

#include "RenderId.fwd.hpp"

namespace graphics
{
class RenderEngine
{
public:
    virtual ~RenderEngine() = default;

    virtual RenderId register_renderable(const glm::vec2& size,
                                         const glm::vec2& position) = 0;
    virtual void deregister(const RenderId&) = 0;
    virtual void set_position(const RenderId&, const glm::vec2& position) = 0;
    virtual void render() = 0;
};
}
