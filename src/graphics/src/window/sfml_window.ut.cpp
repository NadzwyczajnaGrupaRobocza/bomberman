#include <SFML/Window/Event.hpp>
#include <gtest/gtest.h>
#include <range/v3/algorithm/for_each.hpp>

#include "sfml/window_proxy.mock.hpp"
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
    auto create_window()
    {
        return sfml_window{
            size, window_title,
            std::unique_ptr<window_proxy>(unique_window_proxy.release())};
    }

    const std::string window_title = "My Window";
    const window_size size{300, 400};
    const sf::VideoMode mode{size.width, size.height};

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
    const auto closed_event_type = sf::Event::Closed;

    EXPECT_CALL(*proxy, poll_event(_))
        .Times(2)
        .WillOnce(DoAll(SetEventType(ByRef(closed_event_type)), Return(true)))
        .WillOnce(Return(false));
    EXPECT_CALL(*proxy, close());

    window.update();
}
}
