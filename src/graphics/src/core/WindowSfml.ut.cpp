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
    }

    auto create_sfml_window()
    {
        return std::unique_ptr<SfmlWindow>(&sfml_window.get());
    }

    fakeit::Mock<SfmlWindow> sfml_window;
};

TEST_F(WindowSfmlTest, windowShouldCreated)
{
    const std::string window_title = "My Window";
    WindowSize size{300, 400};
    sf::VideoMode mode{size.width, size.height};

    fakeit::Fake(Method(sfml_window, create).Using(mode, window_title));

    WindowSfml window{WindowSize{300, 400}, create_sfml_window()};

    fakeit::Verify(Method(sfml_window, create)).Once();
}

// TEST_F(WindowSfmlTest, windowShouldBeOpenendImmediatelyAfterCreation)
// {
//     WindowSfml window{WindowSize{300, 400}, create_sfml_window()};
//     EXPECT_TRUE(window.is_open());
// }
}
