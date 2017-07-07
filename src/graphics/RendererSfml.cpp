#include "RendererSfml.hpp"

namespace graphics
{
RenderId RendererSfml::register_renderable(const math::Size&,
                                           const math::Position2&)
{
    return RenderId{};
}

void RendererSfml::deregister(const RenderId&)
{
}
void RendererSfml::set_position(const RenderId&, const math::Position2&)
{
}
void RendererSfml::render()
{
}
}
