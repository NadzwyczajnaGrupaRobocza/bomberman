#include "renderer_pool_sfml.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fakeit.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include "sfml_rectangle_shape.hpp"

using namespace ::fakeit;

using ::testing::UnorderedElementsAreArray;

namespace graphics
{
namespace
{
constexpr math::Size2f dummy_size{20, 30};
constexpr math::Size2f another_dummy_size{100, 100};
constexpr math::Position2f dummy_position{0, 10};
constexpr color default_color{0, 0, 0};
}
class renderer_pool_sfml_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        Fake(Dtor(id_generator));
        Fake(Dtor(renderer));
        Fake(Method(renderer, initialize));

        renderer_pool = std::make_unique<renderer_pool_sfml>(
            std::unique_ptr<context_renderer>(&renderer.get()),
            std::unique_ptr<renderer_id_generator>(&id_generator.get()));

        Verify(Method(renderer, initialize));
    }

    auto create_dummy_shape(renderer_id shape_id,
                            const size2f& size = dummy_size,
                            const position2f& position = dummy_position)
    {
        return sfml_rectangle_shape{shape_id, size, position, default_color};
    }

    void expect_render_all(std::vector<sfml_rectangle_shape> expected_shapes)
    {
        std::vector<sfml_rectangle_shape> shapes;
        shapes.reserve(expected_shapes.size());
        Fake(Method(renderer, clear));
        When(Method(renderer, draw)).AlwaysDo([&](const auto& shape) {
            shapes.push_back(shape);
        });

        renderer_pool->render_all();
        ASSERT_THAT(shapes, UnorderedElementsAreArray(expected_shapes));
    }

    void expect_acquire_renderable(const math::Size2f& size,
                                   const math::Position2f& position,
                                   const renderer_id& id)
    {
        EXPECT_EQ(id, renderer_pool->acquire(size, position, default_color));
    }

    void expect_eq_position(const math::Position2f& position,
                            const renderer_id& id)
    {
        EXPECT_FLOAT_EQ(position.x, renderer_pool->get_position(id).x);
        EXPECT_FLOAT_EQ(position.y, renderer_pool->get_position(id).y);
    }

    void expect_move_object(const float x, const float y, const renderer_id& id)
    {
        auto new_position = dummy_position;
        new_position.x += x;
        new_position.y += y;
        renderer_pool->set_position(id, new_position);

        expect_eq_position(new_position, id);
    }

    Mock<renderer_id_generator> id_generator;
    Mock<context_renderer> renderer;
    std::unique_ptr<renderer_pool_sfml> renderer_pool;

    const renderer_id id1{renderer_id_generator{}.generate()};
    const renderer_id id2{renderer_id_generator{}.generate()};
};

TEST_F(renderer_pool_sfml_test, acquireTwoRenderableObject_positionShouldMatch)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2);

    expect_acquire_renderable(dummy_size, dummy_position, id1);
    expect_acquire_renderable(another_dummy_size, dummy_position, id2);
    expect_eq_position(dummy_position, id1);
    expect_eq_position(dummy_position, id2);
}

TEST_F(renderer_pool_sfml_test, renderableObjectShouldBeMovable)
{
    When(Method(id_generator, generate)).Return(id1);
    expect_acquire_renderable(dummy_size, dummy_position, id1);
    expect_eq_position(dummy_position, id1);

    expect_move_object(10, 30, id1);
    expect_move_object(0, -23, id1);
    expect_move_object(-99, 10, id1);
    expect_move_object(10, -231, id1);
}

TEST_F(renderer_pool_sfml_test, getPositionOfInvalidIdShouldThrow)
{
    ASSERT_DEATH(renderer_pool->get_position(id1), "");
}

TEST_F(renderer_pool_sfml_test, setPositiontOfInvalidIdShouldThrow)
{
    ASSERT_DEATH(renderer_pool->set_position(id1, dummy_position), "");
}

TEST_F(renderer_pool_sfml_test, renderAll)
{
    When(Method(id_generator, generate)).AlwaysDo([]() {
        return renderer_id_generator{}.generate();
    });

    auto expected_shapes = {create_dummy_shape(id1, size2f{10, 10}),
                            create_dummy_shape(id1, size2f{710, 30}),
                            create_dummy_shape(id1, size2f{80, 8}),
                            create_dummy_shape(id1, size2f{107, 180}),
                            create_dummy_shape(id1, size2f{60, 30})};

    ranges::for_each(expected_shapes, [this](auto& shape) {
        this->renderer_pool->acquire(shape.getSize(), dummy_position,
                                     default_color);
    });

    expect_render_all({expected_shapes});

    Verify(Method(renderer, clear).Using(sf::Color::Black));
    Verify(Method(renderer, draw))
        .Exactly(static_cast<int>(expected_shapes.size()));
}

TEST_F(renderer_pool_sfml_test, releaseWithoutAcquire_doNothing)
{
    renderer_pool->release(id1);
    Fake(Method(renderer, clear));
    Fake(Method(renderer, draw));
    renderer_pool->render_all();
    Verify(Method(renderer, draw)).Exactly(0);
}

TEST_F(renderer_pool_sfml_test, acquireTwoReleaseOne_shouldRenderOnlyOne)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2);

    EXPECT_EQ(
        id1, renderer_pool->acquire(dummy_size, dummy_position, default_color));
    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          default_color));

    renderer_pool->release(id2);

    auto expected_shapes =
        std::vector<sfml_rectangle_shape>{create_dummy_shape(id1)};

    expect_render_all(expected_shapes);

    Verify(Method(renderer, clear).Using(sf::Color::Black));
    Verify(Method(renderer, draw)).Once();
}

TEST_F(renderer_pool_sfml_test, reacquirenShouldBeRendered)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2).Return(id2);

    EXPECT_EQ(
        id1, renderer_pool->acquire(dummy_size, dummy_position, default_color));
    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          default_color));

    auto expected_shapes =
        std::vector<sfml_rectangle_shape>{create_dummy_shape(id1)};

    renderer_pool->release(id2);
    expect_render_all(expected_shapes);

    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          default_color));
    expected_shapes.emplace_back(id2, another_dummy_size, dummy_position,
                                 default_color);

    expect_render_all(expected_shapes);
}

TEST_F(renderer_pool_sfml_test, acquiredObjectWithSelectedColor)
{
    When(Method(id_generator, generate)).Return(id1);

    const color red{255, 0, 0};
    const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

    EXPECT_EQ(red, renderer_pool->get_color(id));
}

TEST_F(renderer_pool_sfml_test, beAbleToChangeColor)
{
    When(Method(id_generator, generate)).Return(id1);

    const color red{255, 0, 0};
    const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

    const color blue{0, 0, 255};
    renderer_pool->set_color(id, blue);
    EXPECT_EQ(blue, renderer_pool->get_color(id));
}

TEST_F(renderer_pool_sfml_test, render_first_acquired)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2).Return(id2);

    const auto first_id =
        renderer_pool->acquire(dummy_size, dummy_position, default_color);
    const auto second_id = renderer_pool->acquire(
        another_dummy_size, dummy_position, default_color);
    const auto third_id = renderer_pool->acquire(another_dummy_size,
                                                 dummy_position, default_color);

    std::vector<sfml_rectangle_shape> shapes;
    Fake(Method(renderer, clear));
    When(Method(renderer, draw)).AlwaysDo([&](const auto& shape) {
        shapes.push_back(shape);
    });

    renderer_pool->render_all();

    ASSERT_EQ(std::size_t{3}, shapes.size());
    EXPECT_EQ(first_id, shapes[0].get_id());
    EXPECT_EQ(second_id, shapes[1].get_id());
    EXPECT_EQ(third_id, shapes[2].get_id());
}

} // namespace graphics
