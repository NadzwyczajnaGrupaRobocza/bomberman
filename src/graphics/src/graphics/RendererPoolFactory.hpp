#pragma once

#include <memory>

#include "RendererPool.hpp"
#include "WindowSize.hpp"

namespace graphics
{
class RendererPoolFactory
{
public:
    virtual ~RendererPoolFactory() noexcept = default;
    virtual std::unique_ptr<RendererPool> create(const WindowSize&) const;
};
}
