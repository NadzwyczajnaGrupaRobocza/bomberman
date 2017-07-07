#include "RenderEngine.hpp"

#include <gtest/gtest.h>
#include <glm/vec2.hpp>

#include "RenderId.hpp"

namespace graphics
{
class RendererEngineUt : public RenderEngine, public ::testing::Test
{
public:
    void set_position(const RenderId&, const math::Position2&) override
    {
        ASSERT_TRUE(true);
    }

    RenderId register_renderable(const math::Size&,
                                 const math::Position2&) override
    {
        return RenderId{0};
    }

    void deregister(const RenderId&) override
    {
        ASSERT_TRUE(true);
    }

    void render() override
    {
        ASSERT_TRUE(true);
    }
};

TEST_F(RendererEngineUt, register_deregister_renderable)
{
    const math::Size size{1, 1};
    const math::Position2 position{0, 0};

    RenderEngine& r = *this;
    const auto ob = r.register_renderable(size, position);
    r.deregister(ob);
}

TEST_F(RendererEngineUt, set_position)
{
    const RenderId id{546};
    ASSERT_FALSE(id == 56);
    ASSERT_TRUE(id == 546);
    const math::Position2 v2{34, 12};

    RenderEngine& r = *this;
    r.set_position(id, v2);
}

TEST_F(RendererEngineUt, render)
{
    RenderEngine& r = *this;
    r.render();
}
}
