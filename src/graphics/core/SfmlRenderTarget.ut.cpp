#include "SfmlRenderTarget.hpp"

#include <gtest/gtest.h>
#include <fakeit.hpp>

#include "RenderTarget.stub.hpp"

using ::testing::Test;

namespace graphics
{
class RenderTargetBaseFunctionsTest : public Test
{
public:
    RenderTarget<RenderTargetStub> renderTarget{WindowSize{200, 300}};
};

TEST_F(RenderTargetBaseFunctionsTest,
       initializeShouldInvokeInitializeFromBaseClass)
{
    renderTarget.shouldInitialize = true;
    renderTarget.initialize();
}

TEST_F(RenderTargetBaseFunctionsTest, clearShouldInvokeClearFromBaseClass)
{
    auto red = sf::Color::Red;
    renderTarget.expectClear(red);
    renderTarget.clear(red);
}

TEST_F(RenderTargetBaseFunctionsTest, drawShouldInvokeDrawFromBaseClass)
{
    const SfmlRectangleShape shape(Size2f{200, 100}, Position2f(1.f, 2.3f));
    renderTarget.expectDraw(shape);
    renderTarget.draw(shape);
}

TEST(RenderTargetOverridedFuncionsTest, setAndGetSize)
{
    const WindowSize size_200x300{200, 300};
    const WindowSize size_400x300{400, 300};
    SfmlRenderTarget renderTarget200x300{size_200x300};
    SfmlRenderTarget renderTarget400x300{size_400x300};
    EXPECT_EQ(size_200x300, renderTarget200x300.getSize());
    EXPECT_EQ(size_400x300, renderTarget400x300.getSize());
}

TEST(RenderTargetOverridedFuncionsTest,
     activate_dummyMethodShouldJustReturnTrue)
{
    const WindowSize dummy_size{200, 300};
    SfmlRenderTarget renderTarget{dummy_size};
    EXPECT_TRUE(renderTarget.activate(true));
    EXPECT_TRUE(renderTarget.activate(true));
    EXPECT_TRUE(renderTarget.activate(false));
    EXPECT_TRUE(renderTarget.activate(false));
    EXPECT_TRUE(renderTarget.activate(true));
}
}
