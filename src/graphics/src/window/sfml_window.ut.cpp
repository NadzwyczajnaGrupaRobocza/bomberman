#include <gtest/gtest.h>
#include <fakeit.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <SFML/Window/Event.hpp>

#include "sfml_window.hpp"
#include "sfml/window_proxy.mock.hpp"

namespace graphics
{
class sfml_window_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        fakeit::Fake(Dtor(m_window_proxy));
        fakeit::Fake(Method(m_window_proxy, create).Using(mode, window_title));
        fakeit::When(Method(m_window_proxy, is_open)).Return(true);
        fakeit::Fake(Method(m_window_proxy, display));
    }

    auto create_window()
    {
        return sfml_window{size, window_title,
                           std::unique_ptr<window_proxy>(&m_window_proxy.get())};
    }

    void expectPollEvent()
    {
        fakeit::When(Method(m_window_proxy, poll_event))
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

    fakeit::Mock<window_proxy> m_window_proxy;
    std::vector<sf::Event::EventType> events;
};

TEST_F(sfml_window_test, windowShouldCreated)
{
    auto window = create_window();
    fakeit::Verify(Method(m_window_proxy, create)).Once();
}

TEST_F(sfml_window_test, windowShouldBeOpenendImmediatelyAfterCreation)
{
    auto window = create_window();

    EXPECT_TRUE(window.is_open());
    fakeit::Verify(Method(m_window_proxy, is_open)).Once();
}

TEST_F(sfml_window_test, displayWindow)
{
    auto window = create_window();

    window.display();
    fakeit::Verify(Method(m_window_proxy, display)).Once();
}

TEST_F(sfml_window_test, updateWindow)
{
    auto window = create_window();
    prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
                    sf::Event::MouseMoved, sf::Event::MouseEntered});
    const auto no_events = number_of_expected_events();

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(m_window_proxy, poll_event)).Exactly(no_events);
}

TEST_F(sfml_window_test, updateAndCloseWindow)
{
    fakeit::Fake(Method(m_window_proxy, close));
    auto window = create_window();
    prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
                    sf::Event::MouseMoved, sf::Event::MouseEntered,
                    sf::Event::Closed});
    const auto no_events = number_of_expected_events();

    expectPollEvent();
    window.update();
    fakeit::Verify(Method(m_window_proxy, poll_event)).Exactly(no_events);
    fakeit::Verify(Method(m_window_proxy, close)).Once();
}
} // namespace graphics
