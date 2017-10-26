#pragma once

#include "graphics/RendererId.hpp"

namespace graphics
{
class RendererIdGenerator
{
public:
    virtual ~RendererIdGenerator() = default;
    virtual RendererId generate() const;
};
}
