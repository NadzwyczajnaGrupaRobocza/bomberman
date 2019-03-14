#include "sfml_renderer_pool.hpp"

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
} // namespace
class sfml_renderer_pool_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        Fake(Dtor(id_generator));
        Fake(Dtor(renderer));
        Fake(Method(renderer, initialize));

        renderer_pool = std::make_unique<sfml_renderer_pool>(
            std::unique_ptr<context_renderer>(&renderer.get()));

        Verify(Method(renderer, initialize));
    }

    auto create_dummy_shape(const size2f& size = dummy_size,
                            const position2f& position = dummy_position)
    {
        return sfml_rectangle_shape{size, position, graphics::colors::white};
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
    std::unique_ptr<sfml_renderer_pool> renderer_pool;

    const renderer_id id1{renderer_id_generator{}.generate()};
    const renderer_id id2{renderer_id_generator{}.generate()};
};

TEST_F(sfml_renderer_pool_test, acquireTwoRenderableObject_positionShouldMatch)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2);

    EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
                                          graphics::colors::white));

    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          graphics::colors::white));

    expect_eq_position(dummy_position, id1);
    expect_eq_position(dummy_position, id2);
}

TEST_F(sfml_renderer_pool_test, renderableObjectShouldBeMovable)
{
    When(Method(id_generator, generate)).Return(id1);
    EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
                                          graphics::colors::white));
    expect_eq_position(dummy_position, id1);

    expect_move_object(10, 30, id1);
    expect_move_object(0, -23, id1);
    expect_move_object(-99, 10, id1);
    expect_move_object(10, -231, id1);
}

TEST_F(sfml_renderer_pool_test, getPositionOfInvalidIdShouldThrow)
{
    EXPECT_THROW(renderer_pool->get_position(id1), std::out_of_range);
}

TEST_F(sfml_renderer_pool_test, setPositiontOfInvalidIdShouldThrow)
{
    EXPECT_THROW(renderer_pool->set_position(id1, dummy_position),
                 std::out_of_range);
}

TEST_F(sfml_renderer_pool_test, renderAll)
{
    When(Method(id_generator, generate)).AlwaysDo([]() {
        return renderer_id_generator{}.generate();
    });

    auto expected_shapes = {
        create_dummy_shape(size2f{10, 10}), create_dummy_shape(size2f{710, 30}),
        create_dummy_shape(size2f{80, 8}), create_dummy_shape(size2f{107, 180}),
        create_dummy_shape(size2f{60, 30})};

    ranges::for_each(expected_shapes, [this](auto& shape) {
        this->renderer_pool->acquire(shape.getSize(), dummy_position,
                                     graphics::colors::white);
    });

    expect_render_all({expected_shapes});

    Verify(Method(renderer, clear).Using(sf::Color::Black));
    Verify(Method(renderer, draw))
        .Exactly(static_cast<int>(expected_shapes.size()));
}

TEST_F(sfml_renderer_pool_test, releaseWithoutAcquire_doNothing)
{
    renderer_pool->release(id1);
    Fake(Method(renderer, clear));
    Fake(Method(renderer, draw));
    renderer_pool->render_all();
    Verify(Method(renderer, draw)).Exactly(0);
}

TEST_F(sfml_renderer_pool_test, acquireTwoReleaseOne_shouldRenderOnlyOne)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2);

    EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
                                          graphics::colors::white));
    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          graphics::colors::white));

    renderer_pool->release(id2);

    auto expected_shapes = {create_dummy_shape()};

    expect_render_all(expected_shapes);

    Verify(Method(renderer, clear).Using(sf::Color::Black));
    Verify(Method(renderer, draw)).Once();
}

TEST_F(sfml_renderer_pool_test, reacquirenShouldBeRendered)
{
    When(Method(id_generator, generate)).Return(id1).Return(id2).Return(id2);

    EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
                                          graphics::colors::white));
    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          graphics::colors::white));

    std::vector<sfml_rectangle_shape> expected_shapes{create_dummy_shape()};

    renderer_pool->release(id2);
    expect_render_all(expected_shapes);

    EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
                                          graphics::colors::white));
    expected_shapes.emplace_back(another_dummy_size, dummy_position,
                                 graphics::colors::white);

    expect_render_all(expected_shapes);
}

TEST_F(sfml_renderer_pool_test, acquiredObjectWithSelectedColor)
{
    When(Method(id_generator, generate)).Return(id1);

    const color red{255, 0, 0};
    const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

    EXPECT_EQ(red, renderer_pool->get_color(id));
}

TEST_F(sfml_renderer_pool_test, beAbleToChangeColor)
{
    When(Method(id_generator, generate)).Return(id1);

    const color red{255, 0, 0};
    const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

    const color blue{0, 0, 255};
    renderer_pool->set_color(id, blue);
    EXPECT_EQ(blue, renderer_pool->get_color(id));
}
}