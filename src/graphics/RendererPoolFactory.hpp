#pragma once

#include <memory>

#include "RendererPool.hpp"
#include "math/Size.hpp"

namespace graphics
{
class RendererPoolFactory
{
public:
    virtual ~RendererPoolFactory() noexcept = default;
    virtual std::unique_ptr<RendererPool> create(const math::Size&) const = 0;
};
}
