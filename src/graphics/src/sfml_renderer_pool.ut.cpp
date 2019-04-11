#include "sfml_renderer_pool.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include "context_renderer.mock.hpp"
#include "sfml_rectangle_shape.hpp"

using namespace ::testing;

namespace graphics
{
namespace
{
constexpr math::Size2f dummy_size{20, 30};
constexpr math::Size2f another_dummy_size{100, 100};
constexpr math::Position2f dummy_position{0, 10};
}

class sfml_renderer_pool_test : public ::testing::Test
{
public:
    auto create_renderer_pool()
    {
        return std::make_unique<sfml_renderer_pool>(
            std::unique_ptr<context_renderer>(
                unique_context_renderer.release()));
    }

    auto create_object(sfml_renderer_pool& shape_pool, const size2f& shape_size,
                       const position2f& shape_position,
                       const color& shape_color)
    {
        auto const shape_id =
            shape_pool.acquire(shape_size, shape_position, shape_color);
        return sfml_rectangle_shape{shape_id, shape_size, shape_position,
                                    shape_color};
    }

    void expect_eq_position(const math::Position2f& expected,
                            const math::Position2f& position)
    {
        EXPECT_FLOAT_EQ(expected.x, position.x);
        EXPECT_FLOAT_EQ(expected.y, position.y);
    }

    std::unique_ptr<mock_context_renderer> unique_context_renderer{
        std::make_unique<NiceMock<mock_context_renderer>>()};
    mock_context_renderer* context{unique_context_renderer.get()};
};

TEST_F(sfml_renderer_pool_test, contextShouldBeInitializedByRendererPool)
{
    EXPECT_CALL(*context, initialize());
    create_renderer_pool();
}

TEST_F(sfml_renderer_pool_test, acquireTwoRenderableObject_positionShouldMatch)
{
    auto renderer_pool = create_renderer_pool();
    auto const position1 = math::Position2f{30.f, 10.f};
    auto const id1 =
        renderer_pool->acquire(dummy_size, position1, graphics::colors::white);

    auto const position2 = math::Position2f{299.f, 1.f};
    auto const id2 = renderer_pool->acquire(another_dummy_size, position2,
                                            graphics::colors::white);

    expect_eq_position(position1, renderer_pool->get_position(id1));
    expect_eq_position(position2, renderer_pool->get_position(id2));
}

TEST_F(sfml_renderer_pool_test, renderableObjectShouldBeMovable)
{
    auto renderer_pool = create_renderer_pool();
    auto const id = renderer_pool->acquire(dummy_size, dummy_position,
                                           graphics::colors::white);

    expect_eq_position(dummy_position, renderer_pool->get_position(id));

    auto new_position = dummy_position + math::Position2f{10.f, 30.f};
    renderer_pool->set_position(id, new_position);

    expect_eq_position(new_position, renderer_pool->get_position(id));

    new_position = dummy_position + math::Position2f{0.f, -23.f};
    renderer_pool->set_position(id, new_position);

    expect_eq_position(new_position, renderer_pool->get_position(id));

    new_position = dummy_position + math::Position2f{-99.f, 10.f};
    renderer_pool->set_position(id, new_position);

    expect_eq_position(new_position, renderer_pool->get_position(id));

    new_position = dummy_position + math::Position2f{10.f, -231.f};
    renderer_pool->set_position(id, new_position);

    expect_eq_position(new_position, renderer_pool->get_position(id));
}

TEST_F(sfml_renderer_pool_test, getPositionOfInvalidIdShouldThrow)
{
    auto const not_existing_shape_id = renderer_id_generator::generate();
    auto renderer_pool = create_renderer_pool();
    ASSERT_DEATH(renderer_pool->get_position(not_existing_shape_id), "");
}

TEST_F(sfml_renderer_pool_test, setPositiontOfInvalidIdShouldThrow)
{
    auto const not_existing_shape_id = renderer_id_generator::generate();
    auto renderer_pool = create_renderer_pool();
    ASSERT_DEATH(
        renderer_pool->set_position(not_existing_shape_id, dummy_position), "");
}

TEST_F(sfml_renderer_pool_test, renderObject)
{
    auto renderer_pool = create_renderer_pool();
    auto const shape{create_object(*renderer_pool, math::Size2f{10.f, 12.f},
                                   math::Position2f{100.f, 77.f},
                                   graphics::colors::red)};

    EXPECT_CALL(*context, draw(shape));

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, releasedObjectShouldNotBeDrawn)
{
    auto renderer_pool = create_renderer_pool();
    auto const first_shape{create_object(
        *renderer_pool, dummy_size, dummy_position, graphics::colors::red)};

    auto const second_shape{
        create_object(*renderer_pool, math::Size2f{13.f, 11.f},
                      math::Position2f{140.f, 177.f}, graphics::colors::green)};

    renderer_pool->release(first_shape.get_id());

    EXPECT_CALL(*context, draw(second_shape));

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, renderAllObjectInOrderOfCreation)
{
    auto renderer_pool = create_renderer_pool();
    auto const first_shape{
        create_object(*renderer_pool, math::Size2f{10.f, 12.f},
                      math::Position2f{100.f, 77.f}, graphics::colors::red)};

    auto const second_shape{
        create_object(*renderer_pool, math::Size2f{13.f, 11.f},
                      math::Position2f{140.f, 177.f}, graphics::colors::green)};

    InSequence keep_order;

    EXPECT_CALL(*context, draw(first_shape));
    EXPECT_CALL(*context, draw(second_shape));

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, onlyClearTheScreenIfNoObjectToDraw)
{
    auto renderer_pool = create_renderer_pool();

    EXPECT_CALL(*context, clear(sf::Color::Black));
    EXPECT_CALL(*context, draw(_)).Times(0);

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, releaseNotExistingObjectShouldBeIngored)
{
    auto const not_existing_shape_id = renderer_id_generator::generate();
    auto renderer_pool = create_renderer_pool();

    EXPECT_CALL(*context, clear(sf::Color::Black));
    EXPECT_CALL(*context, draw(_)).Times(0);

    renderer_pool->release(not_existing_shape_id);
    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, clearScreenBeforeDraw)
{
    auto renderer_pool = create_renderer_pool();
    auto const shape{create_object(*renderer_pool, dummy_size, dummy_position,
                                   graphics::colors::yellow)};

    InSequence keep_order;

    EXPECT_CALL(*context, clear(sf::Color::Black));
    EXPECT_CALL(*context, draw(shape));

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, createdObjectAfterReleaseOneShouldBeDrawn)
{
    auto renderer_pool = create_renderer_pool();

    auto const first_shape{create_object(
        *renderer_pool, dummy_size, dummy_position, graphics::colors::red)};

    auto const second_shape{
        create_object(*renderer_pool, math::Size2f{13.f, 11.f},
                      math::Position2f{140.f, 177.f}, graphics::colors::red)};

    renderer_pool->release(first_shape.get_id());

    auto const third_shape{
        create_object(*renderer_pool, math::Size2f{10.f, 12.f},
                      math::Position2f{100.f, 77.f}, graphics::colors::red)};

    EXPECT_CALL(*context, draw(second_shape));
    EXPECT_CALL(*context, draw(third_shape));

    renderer_pool->render_all();
}

TEST_F(sfml_renderer_pool_test, acquiredObjectWithSelectedColor)
{
    auto renderer_pool = create_renderer_pool();
    auto const id = renderer_pool->acquire(dummy_size, dummy_position,
                                           graphics::colors::red);

    EXPECT_EQ(graphics::colors::red, renderer_pool->get_color(id));
}

TEST_F(sfml_renderer_pool_test, beAbleToChangeColor)
{
    auto renderer_pool = create_renderer_pool();
    auto const id = renderer_pool->acquire(dummy_size, dummy_position,
                                           graphics::colors::red);

    renderer_pool->set_color(id, graphics::colors::blue);
    EXPECT_EQ(graphics::colors::blue, renderer_pool->get_color(id));
}
}
