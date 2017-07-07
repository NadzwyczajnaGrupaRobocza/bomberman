#pragma once

#include "RenderEngine.hpp"

#include <vector>
namespace graphics
{
class RendererSfml : public RenderEngine
{
public:
    RenderId register_renderable(const math::Size& size,
                                 const math::Position2& position) override;
    void deregister(const RenderId&) override;
    void set_position(const RenderId&,
                      const math::Position2& position) override;
    void render() override;

private:
    std::vector<RenderId> objects;
};
}
