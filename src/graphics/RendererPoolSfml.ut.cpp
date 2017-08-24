#include "RendererPoolSfml.hpp"

#include <gtest/gtest.h>
#include <boost/range/algorithm/sort.hpp>
#include <fakeit.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "SfmlRectangleShape.hpp"
#include "Conversion.hpp"

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

    Mock<RendererIdGenerator> renderer_id_generator;
    Mock<ContextRenderer> context_renderer;
    std::unique_ptr<RendererPoolSfml> renderer_pool;

    const RendererId id1{RendererIdGenerator{}.generate()};
    const RendererId id2{RendererIdGenerator{}.generate()};
    const math::Size dummy_size{20, 30};
    const math::Size another_dummy_size{100, 100};
    const math::Position2 dummy_position{0, 10};
};

TEST_F(RendererPoolSfmlTest, take)
{
    When(Method(renderer_id_generator, generate)).Return(id1).Return(id2);
    sf::Vector2f rect_size{20, 100};

    EXPECT_EQ(id1, renderer_pool->take(dummy_size, dummy_position));
    EXPECT_EQ(id2, renderer_pool->take(dummy_size, dummy_position));
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

    std::vector<SfmlRectangleShape> shapes;
    shapes.reserve(expected_shapes.size());

    Fake(Method(context_renderer, clear));
    When(Method(context_renderer, draw)).AlwaysDo([&](const auto& shape) {
        shapes.push_back(shape);
    });

    boost::for_each(expected_shapes, [this](const auto& shape) {
        this->renderer_pool->take(utils::to_math(shape.getSize()),
                                  dummy_position);
    });
    renderer_pool->render_all();

    boost::sort(expected_shapes);
    boost::sort(shapes);
    for (auto i = 0U; i < expected_shapes.size(); ++i)
    {
        EXPECT_EQ(expected_shapes[i].getSize().x, shapes[i].getSize().x);
        EXPECT_EQ(expected_shapes[i].getSize().y, shapes[i].getSize().y);
    }

    Verify(Method(context_renderer, clear).Using(sf::Color::Black));
    Verify(Method(context_renderer, draw))
        .Exactly(static_cast<int>(expected_shapes.size()));
}
}
