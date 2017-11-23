#include "graphics/RendererPoolFactory.hpp"

#include "RendererPoolSfml.hpp"
#include "RenderTarget.hpp"
#include "RendererIdGenerator.hpp"

namespace graphics
{
std::unique_ptr<RendererPool>
RendererPoolFactory::create(const math::Size2u& window_size) const
{
    return std::make_unique<RendererPoolSfml>(
        std::make_unique<RenderTarget>(window_size),
        std::make_unique<RendererIdGenerator>());
}
}
