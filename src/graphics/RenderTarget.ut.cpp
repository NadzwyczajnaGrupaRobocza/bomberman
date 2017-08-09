#include "RenderTarget.hpp"

#include <gtest/gtest.h>

using ::testing::Test;

namespace graphics
{
TEST(RenderTargetTest, setAndGetSize)
{
    const sf::Vector2u size_200x300{200, 300};
    const sf::Vector2u size_400x300{400, 300};

    RenderTarget renderTarget{size_200x300};
    EXPECT_EQ(size_200x300, renderTarget.getSize());

    renderTarget.setSize(size_400x300);
    EXPECT_EQ(size_400x300, renderTarget.getSize());
}

TEST(RenderTargetTest, activate)
{
    const sf::Vector2u dummy_size{200, 300};
    RenderTarget renderTarget{dummy_size};
    EXPECT_TRUE(renderTarget.activate(true));
    EXPECT_TRUE(renderTarget.activate(true));
    EXPECT_TRUE(renderTarget.activate(false));
    EXPECT_TRUE(renderTarget.activate(false));
    EXPECT_TRUE(renderTarget.activate(true));
}
}
