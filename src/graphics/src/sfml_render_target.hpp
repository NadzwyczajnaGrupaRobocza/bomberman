#pragma once

#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include "boost/numeric/conversion/cast.hpp"

#include "context_renderer.hpp"
#include "window_size.hpp"

namespace graphics
{
namespace
{
// https://github.com/SFML/SFML/wiki/Source:-Letterbox-effect-using-a-view
sf::View getLetterboxView(sf::View view, unsigned windowWidth,
                          unsigned windowHeight)
{
    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox
    // effect. A new view (with a new viewport set) is returned.

    float windowRatio = boost::numeric_cast<float>(windowWidth) /
                        boost::numeric_cast<float>(windowHeight);
    float viewRatio = view.getSize().x / view.getSize().y;
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
    render_target(const window_size& s, const int area_s)
        : size{s}, area_size{area_s}
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

    void draw(const sfml_rectangle_shape& drawable) override
    {
        BaseRenderTarget::draw(drawable);
    }

    void set_view() override
    {
        view.setSize(
            boost::numeric_cast<float>(area_size),
            boost::numeric_cast<float>(
                area_size)); // <- it should be set once, at the startup
        view.setCenter(view.getSize().x / 2,
                       view.getSize().y / 2); // <- only at startup
        view = getLetterboxView(view, size.width,
                                size.height); // <- at startup and every time
                                              // the window size is change
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
    const int area_size;
    sf::View view;
};

using sfml_render_target = render_target<sf::RenderTarget>;
}
