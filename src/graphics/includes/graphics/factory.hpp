#pragma once

#include <memory>

#include "math/Position2f.hpp"
#include "math/Size2u.hpp"

#include "renderer_pool.hpp"
#include "window.hpp"

namespace graphics
{
std::unique_ptr<renderer_pool>
create_renderer_pool(const math::Size2u& rendering_region_size,
                     const math::Size2u& logical_region_size);
std::unique_ptr<window> create_window(const math::Size2u&,
                                      const std::string& title);
}
