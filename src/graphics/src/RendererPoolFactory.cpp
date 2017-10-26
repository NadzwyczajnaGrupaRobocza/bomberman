#include "graphics/RendererPoolFactory.hpp"

#include "RendererPoolSfml.hpp"
#include "RenderTarget.hpp"
#include "RendererIdGenerator.hpp"

namespace graphics
{
std::unique_ptr<RendererPool>
RendererPoolFactory::create(const WindowSize& window_size) const
{
    return std::make_unique<RendererPoolSfml>(
        std::make_unique<RenderTarget>(
            sf::Vector2u(window_size.width, window_size.height)),
        std::make_unique<RendererIdGenerator>());
}
}
