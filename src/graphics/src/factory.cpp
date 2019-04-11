#include "graphics/factory.hpp"

#include "sfml_renderer_pool.hpp"
#include "sfml_render_target.hpp"
#include "window/sfml_window.hpp"
#include "window/sfml_window_proxy.hpp"

namespace graphics
{
std::unique_ptr<renderer_pool>
create_renderer_pool(const math::Size2u& rendering_region_size)
{
    return std::make_unique<sfml_renderer_pool>(
        std::make_unique<sfml_render_target>(rendering_region_size));
}

std::unique_ptr<window> create_window(const math::Size2u& size,
                                      const std::string& title)
{
    return std::make_unique<sfml_window>(
        size, title, std::make_unique<sfml_window_proxy>(size, title));
}
}
