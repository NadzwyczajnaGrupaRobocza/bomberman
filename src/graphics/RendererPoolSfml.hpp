#pragma once

#include "RendererPool.hpp"

#include <vector>
#include <memory>

#include "SfmlRenderTarget.hpp"
#include "DrawableFactory.hpp"

namespace graphics
{
class RendererPoolSfml : public RendererPool
{
public:
    RendererPoolSfml(std::unique_ptr<SfmlRenderTarget>,
                     std::unique_ptr<DrawableFactory>);

    ~RendererPoolSfml() override;

    RenderId take(const math::Size& size,
                  const math::Position2& position) override;
    void give_back(const RenderId&) override;
    void set_position(const RenderId&,
                      const math::Position2& position) override;
    void render_all() override;

private:
    std::unique_ptr<SfmlRenderTarget> window_renderer;
    std::unique_ptr<DrawableFactory> drawable_factory;
    std::vector<RenderId> objects;
};
}
