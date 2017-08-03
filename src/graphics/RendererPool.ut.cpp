#include "RendererPool.hpp"

#include <gtest/gtest.h>
#include <glm/vec2.hpp>

#include "RenderId.hpp"

namespace graphics
{
class RendererPoolUt : public RendererPool, public ::testing::Test
{
public:
    void set_position(const RenderId&, const math::Position2&) override
    {
        ASSERT_TRUE(true);
    }

    RenderId take(const math::Size&, const math::Position2&) override
    {
        return RenderId{0};
    }

    void give_back(const RenderId&) override
    {
        ASSERT_TRUE(true);
    }

    void render_all() override
    {
        ASSERT_TRUE(true);
    }
};

TEST_F(RendererPoolUt, takeAndGiveBack)
{
    const math::Size size{1, 1};
    const math::Position2 position{0, 0};

    RendererPool& r = *this;
    const auto ob = r.take(size, position);
    r.give_back(ob);
}

TEST_F(RendererPoolUt, set_position)
{
    const RenderId id{546};
    ASSERT_FALSE(id == 56);
    ASSERT_TRUE(id == 546);
    const math::Position2 v2{34, 12};

    RendererPool& r = *this;
    r.set_position(id, v2);
}

TEST_F(RendererPoolUt, render_all)
{
    RendererPool& r = *this;
    r.render_all();
}
}
