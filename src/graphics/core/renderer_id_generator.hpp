#pragma once

#include "graphics/renderer_id.hpp"

namespace graphics
{
class RendererIdGenerator
{
public:
    virtual ~RendererIdGenerator() noexcept = default;
    virtual RendererId generate() const;
};
}
