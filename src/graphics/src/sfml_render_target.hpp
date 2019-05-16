#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>

#include "context_renderer.hpp"
#include "window_size.hpp"

namespace graphics
{
template <typename BaseRenderTarget>
class render_target : public context_renderer, public BaseRenderTarget
{
public:
    render_target(const window_size& s) : size{s}
    {
    }

    void initialize() override
    {
        BaseRenderTarget::initialize();
    }

    void clear(const sf::Color& color) override
    {
        BaseRenderTarget::clear(color);
    }

    template <typename Type>
    Type scale(Type val)
    {
        auto h_scale = static_cast<float>(size.height) / 100.0f;
        auto w_scale = static_cast<float>(size.width) / 100.0f;
        auto sf_vec = static_cast<::sf::Vector2f>(val);
        return {sf_vec.x * w_scale, sf_vec.y * h_scale};
    }

    void draw(const sfml_rectangle_shape& drawable) override
    {
        sfml_rectangle_shape ns{drawable.get_id(), scale(drawable.getSize()),
                                scale(drawable.getPosition()),
                                drawable.get_color()};
        BaseRenderTarget::draw(ns);
    }

    sf::Vector2u getSize() const override
    {
        return size;
    }

    bool setActive([[maybe_unused]] bool active) override
    {
        return true;
    }

protected:
    window_size size;
};

using sfml_render_target = render_target<sf::RenderTarget>;
}
