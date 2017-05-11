#include "RenderEngine.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <glm/vec2.hpp>

#include "RenderId.hpp"

namespace graphics
{
class TestRenderer : public RenderEngine, public ::testing::Test
{
public:
    void set_position(const RenderId&, const glm::vec2&) override
    {
        ASSERT_TRUE(true);
    }

    void render() override
    {
        ASSERT_TRUE(true);
    }
};

TEST_F(TestRenderer, set_position)
{
    const RenderId id{546};
    ASSERT_FALSE(id == 56);
    ASSERT_TRUE(id == 546);
    const glm::vec2 v2{34, 12};
    ASSERT_EQ(34, v2.x);
    ASSERT_EQ(12, v2.y);

    RenderEngine& r = *this;
    r.set_position(id, v2);
}

TEST_F(TestRenderer, render)
{
    RenderEngine& r = *this;
    r.render();
}
}
