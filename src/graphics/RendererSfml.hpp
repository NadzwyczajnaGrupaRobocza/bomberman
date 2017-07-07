#pragma once

#include "RenderEngine.hpp"

#include <vector>

#include "RenderId.hpp"

namespace graphics
{
class RendererSfml : public RenderEngine
{
public:
    RenderId register_renderable(const glm::vec2& size,
                                 const glm::vec2& position) override;
    void deregister(const RenderId&) override;
    void set_position(const RenderId&, const glm::vec2& position) override;
    void render() override;

private:
    std::vector<RenderId> objects;
};
}
