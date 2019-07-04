#include "sfml_render_target.hpp"

#include <gtest/gtest.h>

#include "render_target.stub.hpp"
#include "renderer_id_generator.hpp"

using ::testing::Test;

namespace
{
const auto shape_id = graphics::renderer_id_generator{}.generate();
}

namespace graphics
{
class render_target_base_functions_test : public Test
{
public:
    render_target<render_target_stub> renderTarget{window_size{200, 300},
                                                   {100, 100}};
};

TEST_F(render_target_base_functions_test,
       initializeShouldInvokeInitializeFromBaseClass)
{
    renderTarget.shouldInitialize = true;
    renderTarget.initialize();
}

TEST_F(render_target_base_functions_test, clearShouldInvokeClearFromBaseClass)
{
    auto red = sf::Color::Red;
    renderTarget.expectClear(red);
    renderTarget.clear(red);
}

TEST_F(render_target_base_functions_test, drawShouldInvokeDrawFromBaseClass)
{
    const sfml_rectangle_shape shape(shape_id, size2f{200, 100},
                                     position2f(1.f, 2.3f), color{23, 34, 52});
    renderTarget.expectDraw(shape);
    renderTarget.draw(shape);
}

TEST(RenderTargetOverridedFuncionsTest, setAndGetSize)
{
    const window_size size_200x300{200, 300};
    const window_size size_400x300{400, 300};
    sfml_render_target renderTarget200x300{size_200x300, {100, 100}};
    sfml_render_target renderTarget400x300{size_400x300, {100, 100}};
    EXPECT_EQ(size_200x300, renderTarget200x300.getSize());
    EXPECT_EQ(size_400x300, renderTarget400x300.getSize());
}

TEST(RenderTargetOverridedFuncionsTest,
     setActive_dummyMethodShouldJustReturnTrue)
{
    const window_size dummy_size{200, 300};
    sfml_render_target renderTarget{dummy_size, {100, 100}};
    EXPECT_TRUE(renderTarget.setActive(true));
    EXPECT_TRUE(renderTarget.setActive(true));
    EXPECT_TRUE(renderTarget.setActive(false));
    EXPECT_TRUE(renderTarget.setActive(false));
    EXPECT_TRUE(renderTarget.setActive(true));
}
}
