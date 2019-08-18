#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <boost/functional/hash.hpp>

#include "context_renderer.hpp"
#include "graphics/renderer_pool.hpp"
#include "renderer_id_generator.hpp"
#include "texture_warehouse.hpp"

namespace graphics
{
class sfml_renderer_pool : public renderer_pool
{
public:
    sfml_renderer_pool(std::unique_ptr<context_renderer>,
                       std::unique_ptr<texture_warehouse>);

    renderer_id acquire(const math::Size2f&, const math::Position2f&,
                        const color&) override;
    renderer_id acquire(const math::Size2f&, const math::Position2f&,
                        const std::string& texture_path) override;
    void release(const renderer_id&) override;
    void render_all() override;

    void set_position(const renderer_id&,
                      const math::Position2f& position) override;
    math::Position2f get_position(const renderer_id&) override;

    void set_color(const renderer_id&, const color&) override;
    color get_color(const renderer_id&) const override;

    void set_texture(const renderer_id&, const texture_path&) override;
    void set_rendering_size(const math::Size2u&) override;

private:
    void cleanup_unused();

    const sfml_rectangle_shape& get_shape(const renderer_id&) const;
    sfml_rectangle_shape& get_shape(const renderer_id&);

    std::unique_ptr<context_renderer> renderer;
    std::unique_ptr<renderer_id_generator> id_generator;
    std::vector<sfml_rectangle_shape> shapes;
    std::unordered_set<renderer_id, boost::hash<renderer_id>> trash;

    std::unique_ptr<texture_warehouse> textures;
};
}
