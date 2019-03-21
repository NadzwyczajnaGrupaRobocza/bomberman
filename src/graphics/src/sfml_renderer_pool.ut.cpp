#include "sfml_renderer_pool.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fakeit.hpp>
#include <range/v3/algorithm/for_each.hpp>

#include "context_renderer.mock.hpp"
#include "sfml_rectangle_shape.hpp"

using namespace ::fakeit;

using ::testing::NiceMock;
using ::testing::UnorderedElementsAreArray;

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

    auto create_dummy_shape(const size2f& size = dummy_size,
                            const position2f& position = dummy_position)
    {
        return sfml_rectangle_shape{size, position, graphics::colors::white};
    }

    // void expect_render_all(std::vector<sfml_rectangle_shape> expected_shapes)
    // {
    //     std::vector<sfml_rectangle_shape> shapes;
    //     shapes.reserve(expected_shapes.size());
    //     Fake(Method(renderer, clear));
    //     When(Method(renderer, draw)).AlwaysDo([&](const auto& shape) {
    //         shapes.push_back(shape);
    //     });

    //     renderer_pool->render_all();
    //     ASSERT_THAT(shapes, UnorderedElementsAreArray(expected_shapes));
    // }

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
    auto renderer_pool = create_renderer_pool();
    auto const id = renderer_id_generator::generate();
    EXPECT_THROW(renderer_pool->get_position(id), std::out_of_range);
}

TEST_F(sfml_renderer_pool_test, setPositiontOfInvalidIdShouldThrow)
{
    auto renderer_pool = create_renderer_pool();
    auto const id = renderer_id_generator::generate();
    EXPECT_THROW(renderer_pool->set_position(id, dummy_position),
                 std::out_of_range);
}

TEST_F(sfml_renderer_pool_test, renderAll)
{
    auto renderer_pool = create_renderer_pool();
    // auto expected_shapes = {
    //     create_dummy_shape(size2f{10, 10}), create_dummy_shape(size2f{710,
    //     30}), create_dummy_shape(size2f{80, 8}),
    //     create_dummy_shape(size2f{107, 180}), create_dummy_shape(size2f{60,
    //     30})};

    // ranges::for_each(expected_shapes, [this](auto& shape) {
    //     this->renderer_pool->acquire(shape.getSize(), dummy_position,
    //                                  graphics::colors::white);
    // });

    // expect_render_all({expected_shapes});

    // Verify(Method(renderer, clear).Using(sf::Color::Black));
    // Verify(Method(renderer, draw))
    //     .Exactly(static_cast<int>(expected_shapes.size()));
}

// TEST_F(sfml_renderer_pool_test, releaseWithoutAcquire_doNothing)
// {
//     renderer_pool->release(id1);
//     Fake(Method(renderer, clear));
//     Fake(Method(renderer, draw));
//     renderer_pool->render_all();
//     Verify(Method(renderer, draw)).Exactly(0);
// }

// TEST_F(sfml_renderer_pool_test, acquireTwoReleaseOne_shouldRenderOnlyOne)
// {
//     When(Method(id_generator, generate)).Return(id1).Return(id2);

//     EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
//                                           graphics::colors::white));
//     EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
//                                           graphics::colors::white));

//     renderer_pool->release(id2);

//     auto expected_shapes = {create_dummy_shape()};

//     expect_render_all(expected_shapes);

//     Verify(Method(renderer, clear).Using(sf::Color::Black));
//     Verify(Method(renderer, draw)).Once();
// }

// TEST_F(sfml_renderer_pool_test, reacquirenShouldBeRendered)
// {
//     When(Method(id_generator, generate)).Return(id1).Return(id2).Return(id2);

//     EXPECT_EQ(id1, renderer_pool->acquire(dummy_size, dummy_position,
//                                           graphics::colors::white));
//     EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
//                                           graphics::colors::white));

//     std::vector<sfml_rectangle_shape> expected_shapes{create_dummy_shape()};

//     renderer_pool->release(id2);
//     expect_render_all(expected_shapes);

//     EXPECT_EQ(id2, renderer_pool->acquire(another_dummy_size, dummy_position,
//                                           graphics::colors::white));
//     expected_shapes.emplace_back(another_dummy_size, dummy_position,
//                                  graphics::colors::white);

//     expect_render_all(expected_shapes);
// }

// TEST_F(sfml_renderer_pool_test, acquiredObjectWithSelectedColor)
// {
//     When(Method(id_generator, generate)).Return(id1);

//     const color red{255, 0, 0};
//     const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

//     EXPECT_EQ(red, renderer_pool->get_color(id));
// }

// TEST_F(sfml_renderer_pool_test, beAbleToChangeColor)
// {
//     When(Method(id_generator, generate)).Return(id1);

//     const color red{255, 0, 0};
//     const auto id = renderer_pool->acquire(dummy_size, dummy_position, red);

//     const color blue{0, 0, 255};
//     renderer_pool->set_color(id, blue);
//     EXPECT_EQ(blue, renderer_pool->get_color(id));
// }
}
