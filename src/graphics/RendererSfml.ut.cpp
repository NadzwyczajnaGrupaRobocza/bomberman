#include "RendererSfml.hpp"

#include <gtest/gtest.h>

using ::testing::Test;

namespace graphics
{
class RendererSfmlTest : public Test
{
public:
    RendererSfml renderer;
};

TEST_F(RendererSfmlTest, test)
{
    ASSERT_TRUE(true);
}
}
