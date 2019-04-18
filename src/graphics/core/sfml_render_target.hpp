#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include "context_renderer.hpp"
#include "window_size.hpp"

namespace graphics
{
namespace
{
//https://github.com/SFML/SFML/wiki/Source:-Letterbox-effect-using-a-view
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox
    // effect. A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and
    // right side. Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}
}
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
        BaseRenderTarget::draw(drawable);
    }

    void set_view() override
    {
        float map_width{100};
        float map_height{100};

        view.setSize(map_width, map_height); // <- it should be set once, at the startup
        view.setCenter(view.getSize().x / 2, view.getSize().y / 2); // <- only at startup
        view = getLetterboxView( view, size.width, size.height); // <- at startup and every time the window size is change
        BaseRenderTarget::setView(view);
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
    sf::View view;
};

using sfml_render_target = render_target<sf::RenderTarget>;
}
