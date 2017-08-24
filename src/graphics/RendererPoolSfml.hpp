#pragma once

#include "RendererPool.hpp"

#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/functional/hash.hpp>

#include "ContextRenderer.hpp"
#include "RendererIdGenerator.hpp"

namespace graphics
{
class RendererPoolSfml : public RendererPool
{
public:
    RendererPoolSfml(std::unique_ptr<ContextRenderer>,
                     std::unique_ptr<RendererIdGenerator>);

    RendererId take(const math::Size& size,
                    const math::Position2& position) override;
    void give_back(const RendererId&) override;
    void cleanup_unused() override;
    void render_all() override;

    void set_position(const RendererId&,
                      const math::Position2& position) override;

private:
    std::unique_ptr<ContextRenderer> context_renderer;
    std::unique_ptr<RendererIdGenerator> renderer_id_generator;
    std::unordered_map<RendererId, SfmlRectangleShape, boost::hash<RendererId>>
        shapes;
};
}
