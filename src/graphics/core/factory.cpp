#include "graphics/factory.hpp"

#include "renderer_pool_sfml.hpp"
#include "sfml_render_target.hpp"
#include "renderer_id_generator.hpp"
#include "window_sfml.hpp"
#include "sfml_window_facade.hpp"

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
