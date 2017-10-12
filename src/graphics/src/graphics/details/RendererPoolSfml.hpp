#pragma once

#include "RendererPool.hpp"

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
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

    RendererId take(const Size&, const Position&) override;
    void give_back(const RendererId&) override;
    void render_all() override;

    void set_position(const RendererId&, const Position& position) override;
    Position get_position(const RendererId&) override;

private:
    void cleanup_unused();

    std::unique_ptr<ContextRenderer> context_renderer;
    std::unique_ptr<RendererIdGenerator> renderer_id_generator;
    std::unordered_map<RendererId, SfmlRectangleShape, boost::hash<RendererId>>
        shapes;
    std::unordered_set<RendererId, boost::hash<RendererId>> trash;
};
}
