#include <gtest/gtest.h>
#include <fakeit.hpp>
#include <range/v3/algorithm/for_each.hpp>

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
        fakeit::When(Method(sfml_window, is_open)).Return(true);
        fakeit::Fake(Method(sfml_window, display));
    }

    auto create_window()
    {
        return WindowSfml{size, window_title,
                          std::unique_ptr<SfmlWindow>(&sfml_window.get())};
    }

    void expectPollEvent()
    {
        fakeit::When(Method(sfml_window, poll_event))
            .AlwaysDo([&](sf::Event& e) {
                e.type = events.back();
                events.pop_back();
                return not events.empty();
            });
    }

    int prepare_events(std::vector<sf::Event::EventType>&& e)
    {
        events = std::move(e);
        return static_cast<int>(events.size());
    }

    const std::string window_title = "My Window";
    const WindowSize size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

    fakeit::Mock<SfmlWindow> sfml_window;
    std::vector<sf::Event::EventType> events;
};

TEST_F(WindowSfmlTest, windowShouldCreated)
{
    auto window = create_window();
    fakeit::Verify(Method(sfml_window, create)).Once();
}

TEST_F(WindowSfmlTest, windowShouldBeOpenendImmediatelyAfterCreation)
{
    auto window = create_window();

    EXPECT_TRUE(window.is_open());
    fakeit::Verify(Method(sfml_window, is_open)).Once();
}

TEST_F(WindowSfmlTest, displayWindow)
{
    auto window = create_window();

    window.display();
    fakeit::Verify(Method(sfml_window, display)).Once();
}

TEST_F(WindowSfmlTest, updateWindow)
{
    auto window = create_window();
    const auto expected_polled_events =
        prepare_events({sf::Event::MouseLeft, sf::Event::TouchBegan,
                        sf::Event::MouseMoved, sf::Event::MouseEntered});

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(sfml_window, poll_event))
        .Exactly(expected_polled_events);
}

TEST_F(WindowSfmlTest, updateAndCloseWindow)
{
    fakeit::Fake(Method(sfml_window, close));
    auto window = create_window();
    const auto expected_polled_events = prepare_events(
        {sf::Event::MouseLeft, sf::Event::TouchBegan, sf::Event::MouseMoved,
         sf::Event::MouseEntered, sf::Event::Closed});

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(sfml_window, poll_event))
        .Exactly(expected_polled_events);
    fakeit::Verify(Method(sfml_window, close)).Once();
}
}
