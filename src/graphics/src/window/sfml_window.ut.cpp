#include <gtest/gtest.h>
#include <range/v3/algorithm/for_each.hpp>
#include <SFML/Window/Event.hpp>

#include "sfml_window.hpp"
#include "sfml/window_proxy.mock.hpp"

using namespace ::testing;

namespace graphics
{
class DISABLED_sfml_window_test : public Test
{
public:
    auto create_window()
    {
        auto w = std::make_unique<StrictMock<mock_window_proxy>>();
        m_mock_window_proxy = w.get();
        return sfml_window{size, window_title,
                           std::unique_ptr<window_proxy>(w.release())};
    }

    const std::string window_title = "My Window";
    const window_size size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

    mock_window_proxy* m_mock_window_proxy;
    std::vector<sf::Event::EventType> events;
};

TEST_F(DISABLED_sfml_window_test, windowShouldCreated)
{
    //TODO
    // EXPECT_CALL(*m_mock_window_proxy, create());
    auto window = create_window();
}

TEST_F(DISABLED_sfml_window_test, windowShouldBeOpenendImmediatelyAfterCreation)
{
    auto window = create_window();

    EXPECT_CALL(*m_mock_window_proxy, is_open()).WillOnce(Return(true));
    EXPECT_TRUE(window.is_open());

    EXPECT_CALL(*m_mock_window_proxy, is_open()).WillOnce(Return(false));
    EXPECT_FALSE(window.is_open());
}

TEST_F(DISABLED_sfml_window_test, displayWindow)
{
    auto window = create_window();

    EXPECT_CALL(*m_mock_window_proxy, display());
    window.display();
}

TEST_F(DISABLED_sfml_window_test, updateWindow)
{
    //TODO:
    auto window = create_window();
    // prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
    //                 sf::Event::MouseMoved, sf::Event::MouseEntered});
    // const auto no_events = number_of_expected_events();

    // expectPollEvent();
    EXPECT_CALL(*m_mock_window_proxy, poll_event(_)).Times(0);
    window.update();
    // fakeit::Verify(Method(m_window_proxy, poll_event)).Exactly(no_events);
}

TEST_F(DISABLED_sfml_window_test, updateAndCloseWindow)
{
    //TODO:
    // fakeit::Fake(Method(m_window_proxy, close));
    auto window = create_window();
    // prepare_events({sf::Event::MouseLeft, sf::Event::LostFocus,
    //                 sf::Event::MouseMoved, sf::Event::MouseEntered,
    //                 sf::Event::Closed});
    // const auto no_events = number_of_expected_events();

    // expectPollEvent();
    window.update();
    EXPECT_CALL(*m_mock_window_proxy, poll_event(_)).Times(0);
    // fakeit::Verify(Method(m_window_proxy, poll_event)).Exactly(no_events);
    // fakeit::Verify(Method(m_window_proxy, close)).Once();
}
} // namespace graphics
