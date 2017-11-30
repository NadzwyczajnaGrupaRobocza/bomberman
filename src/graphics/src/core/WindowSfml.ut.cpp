#include <gtest/gtest.h>
#include <fakeit.hpp>

#include "WindowSfml.hpp"

#include <iostream>

namespace graphics
{
class WindowSfmlTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        fakeit::Fake(Dtor(sfml_window));
        fakeit::Fake(Method(sfml_window, create).Using(mode, window_title));
    }

    auto create_window(const WindowSize& size, const std::string& title)
    {
        WindowSfml{size, title,
                   std::make_unique<SfmlWindow>(&sfml_window.get())};
    }

    const std::string window_title = "My Window";
    const WindowSize size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

    fakeit::Mock<SfmlWindow> sfml_window;
};

TEST_F(WindowSfmlTest, windowShouldCreatedAndOpened)
{
    auto window = create_window(WindowSize{300, 400}, window_title);
    fakeit::Verify(Method(sfml_window, create)).Once();
    EXPECT_TRUE(window.is_open());
}

// TEST_F(WindowSfmlTest, windowShouldBeOpenendImmediatelyAfterCreation)
// {
//     auto window = create_window(WindowSize{300, 400}, window_title);
//     EXPECT_TRUE(window.is_open());
// }
}
