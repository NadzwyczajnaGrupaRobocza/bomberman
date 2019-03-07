#pragma once

#include "graphics/renderer_pool.hpp"

#include <boost/functional/hash.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "context_renderer.hpp"
#include "renderer_id_generator.hpp"

namespace graphics
{
class renderer_pool_sfml : public renderer_pool
{
public:
    renderer_pool_sfml(std::unique_ptr<context_renderer>,
                       std::unique_ptr<renderer_id_generator>);

    renderer_id acquire(const math::Size2f&, const math::Position2f&,
                        const color&) override;
    void release(const renderer_id&) override;
    void render_all() override;

    void set_position(const renderer_id&,
                      const math::Position2f& position) override;
    math::Position2f get_position(const renderer_id&) override;

    void set_color(const renderer_id&, const color&) override;
    color get_color(const renderer_id&) const override;

private:
    void cleanup_unused();

    std::unique_ptr<context_renderer> renderer;
    std::unique_ptr<renderer_id_generator> id_generator;
    std::unordered_map<renderer_id, sfml_rectangle_shape,
                       boost::hash<renderer_id>>
        shapes;
    std::unordered_set<renderer_id, boost::hash<renderer_id>> trash;
};
} // namespace graphics
