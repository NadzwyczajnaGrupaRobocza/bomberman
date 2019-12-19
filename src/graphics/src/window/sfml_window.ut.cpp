#include <range/v3/algorithm/for_each.hpp>

#include <SFML/Window/Event.hpp>
#include <gtest/gtest.h>

#include "graphics/window_change_observer.mock.hpp"
#include "sfml/window_proxy.mock.hpp"

#include "graphics/window_event.hpp"
#include "sfml_window.hpp"

using namespace ::testing;

namespace graphics
{
ACTION_P(SetEventType, event_type)
{
    arg0.type = event_type;
}

class sfml_window_test : public Test
{
public:
    auto create_window(window_change_observer& window_observer)
    {
        return sfml_window{
            size, window_title,
            std::unique_ptr<window_proxy>(unique_window_proxy.release()),
            window_observer};
    }

    auto create_window()
    {
        return sfml_window{
            size, window_title,
            std::unique_ptr<window_proxy>(unique_window_proxy.release())};
    }

    void expect_poll_event(sf::Event event)
    {
        EXPECT_CALL(*proxy, poll_event(_))
            .Times(2)
            .WillOnce(DoAll(SetArgReferee<0>(event), Return(true)))
            .WillOnce(Return(false));
    }

    const std::string window_title = "My Window";
    const window_size size{300, 400};
    const sf::VideoMode mode{size.width, size.height};
    window_change_observer_mock observer;

    std::unique_ptr<mock_window_proxy> unique_window_proxy{
        std::make_unique<NiceMock<mock_window_proxy>>()};
    mock_window_proxy* proxy{unique_window_proxy.get()};
};

TEST_F(sfml_window_test, windowShouldCreated)
{
    EXPECT_CALL(*proxy, create(sf::VideoMode{size.width, size.height},
                               sf::String{window_title}));
    auto window = create_window();
}

TEST_F(sfml_window_test, windowShouldBeOpenendImmediatelyAfterCreation)
{
    auto window = create_window();

    EXPECT_CALL(*proxy, is_open()).WillOnce(Return(true));
    EXPECT_TRUE(window.is_open());

    EXPECT_CALL(*proxy, is_open()).WillOnce(Return(false));
    EXPECT_FALSE(window.is_open());
}

TEST_F(sfml_window_test, displayWindow)
{
    auto window = create_window();

    EXPECT_CALL(*proxy, display());
    window.display();
}

TEST_F(sfml_window_test, updateDoNothingIfNoPollEvents)
{
    unique_window_proxy = std::make_unique<StrictMock<mock_window_proxy>>();
    proxy = unique_window_proxy.get();
    EXPECT_CALL(*proxy, create(_, _)).Times(AnyNumber());
    auto window = create_window();

    EXPECT_CALL(*proxy, poll_event(_)).Times(1).WillOnce(Return(false));
    window.update();
}

TEST_F(sfml_window_test, updateAndCloseWindow)
{
    auto window = create_window();
    sf::Event close_event;
    const auto closed_event_type = sf::Event::Closed;
    close_event.type = closed_event_type;

    expect_poll_event(close_event);
    EXPECT_CALL(*proxy, close());

    window.update();
}

// --------------------------- UPDATE_SIZE  ---------------------------

struct sfml_window_test_update_size : sfml_window_test
{
    void SetUp() override
    {
        sf::Event resized_event;
        resized_event.type = sf::Event::Resized;
        expect_poll_event(resized_event);
    }

    window_size tested_window_size{2, 88};
};

TEST_F(sfml_window_test_update_size, shouldCallObserver)
{
    math::Size2u size_read{2, 88};

    EXPECT_CALL(*proxy, get_window_size()).WillOnce(Return(size_read));
    EXPECT_CALL(observer, window_size_changed(tested_window_size));

    auto window = create_window(observer);
    window.update();
}

TEST_F(sfml_window_test_update_size, whenNoObserver_shouldNotCallObserver)
{
    auto window = create_window();
    window.update();
}

// --------------------------- NOTIFY  ---------------------------

struct sfml_window_test_notify : sfml_window_test,
                                 WithParamInterface<std::pair<sf::Event, bool>>
{
    void SetUp() override
    {
        window.subscribe([this](const window_event&) { lambda_called = true; });
    }

    void expect_poll(sf::Event event)
    {
        expect_poll_event(event);
    }

    sfml_window window{create_window()};
    bool lambda_called = false;
};

TEST_P(sfml_window_test_notify, not_pass_to_subscriber)
{
    const auto param = GetParam();
    const auto& event = param.first;
    const auto expected_result = param.second;

    expect_poll(event);

    window.update();

    EXPECT_EQ(expected_result, lambda_called);
}

INSTANTIATE_TEST_CASE_P(
    sfml_window_test_notify_unexpected_events, sfml_window_test_notify,
    Values(std::make_pair(sf::Event{sf::Event::GainedFocus, {}}, false)));

INSTANTIATE_TEST_CASE_P(
    sfml_window_test_notify_expected_events, sfml_window_test_notify,
    Values(std::make_pair(sf::Event{sf::Event::Resized, {}}, true),
           std::make_pair(sf::Event{sf::Event::Closed, {}}, true)));
}
