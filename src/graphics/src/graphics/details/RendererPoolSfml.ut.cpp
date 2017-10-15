#include "RendererPoolSfml.hpp"

#include <gtest/gtest.h>
#include <fakeit.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include "SfmlRectangleShape.hpp"

using namespace ::testing;
using namespace ::fakeit;

namespace graphics
{
class RendererPoolSfmlTest : public Test
{
public:
    void SetUp() override
    {
        ASSERT_NE(id1, id2);
        Fake(Dtor(renderer_id_generator));
        Fake(Dtor(context_renderer));
        Fake(Method(context_renderer, initialize));

        renderer_pool = std::make_unique<RendererPoolSfml>(
            std::unique_ptr<ContextRenderer>(&context_renderer.get()),
            std::unique_ptr<RendererIdGenerator>(&renderer_id_generator.get()));

        Verify(Method(context_renderer, initialize));
    }

    void expect_render_all(std::vector<SfmlRectangleShape> expected_shapes)
    {
        std::vector<SfmlRectangleShape> shapes;
        shapes.reserve(expected_shapes.size());
        Fake(Method(context_renderer, clear));
        When(Method(context_renderer, draw)).AlwaysDo([&](const auto& shape) {
            shapes.push_back(shape);
        });

        renderer_pool->render_all();

        boost::sort(expected_shapes);
        boost::sort(shapes);
        for (auto i = 0U; i < expected_shapes.size(); ++i)
        {
            EXPECT_EQ(expected_shapes[i].getSize().x, shapes[i].getSize().x);
            EXPECT_EQ(expected_shapes[i].getSize().y, shapes[i].getSize().y);
        }
    }

    void expectTakeRenderable(const Size& size, const Position& position,
                              const RendererId& id)
    {
        EXPECT_EQ(id, renderer_pool->take(size, position));
    }

    void expectEqPosition(const Position& position, const RendererId& id)
    {
        EXPECT_FLOAT_EQ(position.x, renderer_pool->get_position(id).x);
        EXPECT_FLOAT_EQ(position.y, renderer_pool->get_position(id).y);
    }

    Mock<RendererIdGenerator> renderer_id_generator;
    Mock<ContextRenderer> context_renderer;
    std::unique_ptr<RendererPoolSfml> renderer_pool;

    const RendererId id1{RendererIdGenerator{}.generate()};
    const RendererId id2{RendererIdGenerator{}.generate()};
    const Size dummy_size{20, 30};
    const Size another_dummy_size{100, 100};
    const Position dummy_position{0, 10};
};

TEST_F(RendererPoolSfmlTest, takeTwoRenderableObject_positionShouldMatch)
{
    When(Method(renderer_id_generator, generate)).Return(id1).Return(id2);

    expectTakeRenderable(dummy_size, dummy_position, id1);
    expectTakeRenderable(another_dummy_size, dummy_position, id2);
    expectEqPosition(dummy_position, id1);
    expectEqPosition(dummy_position, id2);
}

TEST_F(RendererPoolSfmlTest, renderableObjectShouldBeMovable)
{
    When(Method(renderer_id_generator, generate)).Return(id1);
    expectTakeRenderable(dummy_size, dummy_position, id1);
    expectEqPosition(dummy_position, id1);

    auto new_position = dummy_position;
    new_position.x += 10;
    renderer_pool->set_position(id1, new_position);

    expectEqPosition(new_position, id1);
}

TEST_F(RendererPoolSfmlTest, getPositionOfInvalidIdShouldThrow)
{
    EXPECT_THROW(renderer_pool->get_position(id1), std::out_of_range);
}

TEST_F(RendererPoolSfmlTest, setPositiontOfInvalidIdShouldThrow)
{
    EXPECT_THROW(renderer_pool->set_position(id1, dummy_position),
                 std::out_of_range);
}

TEST_F(RendererPoolSfmlTest, renderAll)
{
    When(Method(renderer_id_generator, generate)).AlwaysDo([]() {
        return RendererIdGenerator{}.generate();
    });

    std::vector<SfmlRectangleShape> expected_shapes = {
        SfmlRectangleShape{sf::Vector2f{10, 10}},
        SfmlRectangleShape{sf::Vector2f{710, 30}},
        SfmlRectangleShape{sf::Vector2f{80, 8}},
        SfmlRectangleShape{sf::Vector2f{107, 180}},
        SfmlRectangleShape{sf::Vector2f{60, 30}}};

    boost::for_each(expected_shapes, [this](const auto& shape) {
        this->renderer_pool->take(Size{shape.getSize().x, shape.getSize().y},
                                  dummy_position);
    });

    expect_render_all({expected_shapes});

    Verify(Method(context_renderer, clear).Using(sf::Color::Black));
    Verify(Method(context_renderer, draw))
        .Exactly(static_cast<int>(expected_shapes.size()));
}

TEST_F(RendererPoolSfmlTest, giveBackWithoutTake)
{
    renderer_pool->give_back(id1);
    Fake(Method(context_renderer, clear));
    renderer_pool->render_all();
}

TEST_F(RendererPoolSfmlTest, takeAndGiveBack_shouldStillBeAvailable)
{
    // When(Method(renderer_id_generator, generate)).Return(id1);
    // EXPECT_EQ(id1, renderer_pool->take(dummy_size, dummy_position));
    // renderer_pool->give_back(id1);
    // expect_render_all({SfmlRectangleShape{
    //     sf::Vector2f{dummy_size.width, dummy_size.height}}});
}

TEST_F(RendererPoolSfmlTest, takeTwoGiveBackOne_shouldRenderOnlyOne)
{
    When(Method(renderer_id_generator, generate)).Return(id1).Return(id2);

    EXPECT_EQ(id1, renderer_pool->take(dummy_size, dummy_position));
    EXPECT_EQ(id2, renderer_pool->take(another_dummy_size, dummy_position));

    renderer_pool->give_back(id2);

    std::vector<SfmlRectangleShape> expected_shapes = {
        SfmlRectangleShape{sf::Vector2f{dummy_size.width, dummy_size.height}}};

    expect_render_all(expected_shapes);

    Verify(Method(context_renderer, clear).Using(sf::Color::Black));
    Verify(Method(context_renderer, draw)).Exactly(1);
}

TEST_F(RendererPoolSfmlTest, retakenShouldBeRendered)
{
    When(Method(renderer_id_generator, generate))
        .Return(id1)
        .Return(id2)
        .Return(id2);

    EXPECT_EQ(id1, renderer_pool->take(dummy_size, dummy_position));
    EXPECT_EQ(id2, renderer_pool->take(another_dummy_size, dummy_position));

    std::vector<SfmlRectangleShape> expected_shapes{
        SfmlRectangleShape{sf::Vector2f{dummy_size.width, dummy_size.height}}};

    renderer_pool->give_back(id2);
    expect_render_all(expected_shapes);

    EXPECT_EQ(id2, renderer_pool->take(another_dummy_size, dummy_position));
    expected_shapes.emplace_back(
        sf::Vector2f{another_dummy_size.width, another_dummy_size.height});

    expect_render_all(expected_shapes);

    // Verify(Method(context_renderer,
    // clear).Using(sf::Color::Black)).Exactly(2);
    // Verify(Method(context_renderer, draw)).Exactly(3);
}
}
