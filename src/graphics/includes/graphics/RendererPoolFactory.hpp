#pragma once

#include <memory>

#include "math/Size2u.hpp"

#include "RendererPool.hpp"

namespace graphics
{
class RendererPoolFactory
{
public:
    virtual ~RendererPoolFactory() noexcept = default;
    virtual std::unique_ptr<RendererPool>
    create(const math::Size2u& window_size) const;
};
}
