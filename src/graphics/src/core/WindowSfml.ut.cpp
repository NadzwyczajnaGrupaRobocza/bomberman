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

    auto create_window()
    {
        return WindowSfml{size, window_title,
                          std::unique_ptr<SfmlWindow>(&sfml_window.get())};
    }

    const std::string window_title = "My Window";
    const WindowSize size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

    fakeit::Mock<SfmlWindow> sfml_window;
};

TEST_F(WindowSfmlTest, windowShouldCreated)
{
    auto window = create_window();
    fakeit::Verify(Method(sfml_window, create)).Once();
}

// TEST_F(WindowSfmlTest, windowShouldBeOpenendImmediatelyAfterCreation)
// {
//     auto window = create_window(WindowSize{300, 400}, window_title);
//     EXPECT_TRUE(window.is_open());
// }
}
