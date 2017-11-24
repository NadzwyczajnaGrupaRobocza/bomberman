#include "graphics/RendererPoolFactory.hpp"

#include "RendererPoolSfml.hpp"
#include "RenderTarget.hpp"
#include "RendererIdGenerator.hpp"
#include "WindowSfml.hpp"
#include "SfmlWindowFacade.hpp"

namespace graphics
{
std::unique_ptr<RendererPool>
create_renderer_pool(const math::Size2u& rendering_region_size)
{
    return std::make_unique<RendererPoolSfml>(
        std::make_unique<RenderTarget>(rendering_region_size),
        std::make_unique<RendererIdGenerator>());
}

std::unique_ptr<Window> create_window(const math::Size2u& size)
{
    return std::make_unique<WindowSfml>(size, std::make_unique<SfmlWindowFacade>());
}
}
