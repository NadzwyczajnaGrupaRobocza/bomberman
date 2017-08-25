#include "../RendererPoolFactory.hpp"

#include "RendererPoolSfml.hpp"
#include "RenderTarget.hpp"
#include "RendererIdGenerator.hpp"
#include "Conversion.hpp"

namespace graphics
{
std::unique_ptr<RendererPool>
RendererPoolFactory::create(const math::Size& window_size) const
{
    return std::make_unique<RendererPoolSfml>(
        std::make_unique<RenderTarget>(utils::to_sfml_u(window_size)),
        std::make_unique<RendererIdGenerator>());


}
}
