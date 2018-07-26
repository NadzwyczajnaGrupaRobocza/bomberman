#include "graphics/Factory.hpp"

#include "RendererPoolSfml.hpp"
#include "SfmlRenderTarget.hpp"
#include "RendererIdGenerator.hpp"
#include "WindowSfml.hpp"
#include "SfmlWindowFacade.hpp"

namespace graphics
{
std::unique_ptr<renderer_pool>
create_renderer_pool(const math::Size2u& rendering_region_size)
{
    return std::make_unique<renderer_pool_sfml>(
        std::make_unique<sfml_render_target>(rendering_region_size),
        std::make_unique<renderer_id_generator>());
}

std::unique_ptr<window> create_window(const math::Size2u& size,
                                      const std::string& title)
{
    return std::make_unique<window_sfml>(
        size, title, std::make_unique<sfml_window_facade>(size, title));
}
}
