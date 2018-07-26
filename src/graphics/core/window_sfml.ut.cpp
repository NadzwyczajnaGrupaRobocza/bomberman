#include <gtest/gtest.h>
#include <fakeit.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <SFML/Window/Event.hpp>

#include "window_sfml.hpp"

namespace graphics
{
class window_sfml_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        fakeit::Fake(Dtor(mock_window));
        fakeit::Fake(Method(mock_window, create).Using(mode, window_title));
        fakeit::When(Method(mock_window, is_open)).Return(true);
        fakeit::Fake(Method(mock_window, display));
    }

    auto create_window()
    {
        return window_sfml{size, window_title,
                          std::unique_ptr<sfml_window>(&mock_window.get())};
    }

    void expectPollEvent()
    {
        fakeit::When(Method(mock_window, poll_event))
            .AlwaysDo([&](sf::Event& e) {
                e.type = events.back();
                events.pop_back();
                return not events.empty();
            });
    }

    void prepare_events(std::vector<sf::Event::EventType>&& e)
    {
        events = std::move(e);
    }

    int number_of_expected_events() const
    {
        return static_cast<int>(events.size());
    }

    const std::string window_title = "My Window";
    const window_size size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

    fakeit::Mock<sfml_window> mock_window;
    std::vector<sf::Event::EventType> events;
};

TEST_F(window_sfml_test, windowShouldCreated)
{
    auto window = create_window();
    fakeit::Verify(Method(mock_window, create)).Once();
}

TEST_F(window_sfml_test, windowShouldBeOpenendImmediatelyAfterCreation)
{
    auto window = create_window();

    EXPECT_TRUE(window.is_open());
    fakeit::Verify(Method(mock_window, is_open)).Once();
}

TEST_F(window_sfml_test, displayWindow)
{
    auto window = create_window();

    window.display();
    fakeit::Verify(Method(mock_window, display)).Once();
}

TEST_F(window_sfml_test, updateWindow)
{
    auto window = create_window();
    prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
                    sf::Event::MouseMoved, sf::Event::MouseEntered});
    const auto no_events = number_of_expected_events();

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(mock_window, poll_event)).Exactly(no_events);
}

TEST_F(window_sfml_test, updateAndCloseWindow)
{
    fakeit::Fake(Method(mock_window, close));
    auto window = create_window();
    prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
                    sf::Event::MouseMoved, sf::Event::MouseEntered,
                    sf::Event::Closed});
    const auto no_events = number_of_expected_events();

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(mock_window, poll_event)).Exactly(no_events);
    fakeit::Verify(Method(mock_window, close)).Once();
}
}
