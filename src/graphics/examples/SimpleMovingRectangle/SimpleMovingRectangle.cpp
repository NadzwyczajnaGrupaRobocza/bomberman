#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <cmath>
#include <iostream>
#include <gsl/gsl_util>
#include <chrono>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>

#include "graphics/RendererPoolFactory.hpp"
#include "graphics/Size.hpp"
#include "graphics/WindowSize.hpp"
#include "graphics/Position.hpp"

using Arrow = std::vector<std::pair<int, graphics::RendererId>>;

inline auto create_object_at_center(const graphics::WindowSize& window_size,
                                    graphics::RendererPool& renderer_pool)
{
    using namespace graphics;
    return renderer_pool.take(
        Size{15, 15},
        Position{window_size.width / 2.0f, window_size.height / 2.0f});
}

inline auto create_arrow_from_point(const graphics::Position& point,
                                    const std::uint32_t& arrow_length,
                                    const std::uint32_t& arrow_body_density,
                                    graphics::RendererPool& renderer_pool)
{
    using namespace graphics;
    const auto point_count = arrow_length / arrow_body_density;
    float current_pos = arrow_body_density;

    Arrow arrow(point_count);
    ranges::generate(arrow, [&] {
        const auto distance_from_center = current_pos;
        current_pos += arrow_body_density;
        return std::make_pair(distance_from_center,
                              renderer_pool.take(Size{20, 30}, point));
    });
    return arrow;
}

inline auto calculate_pi()
{
    return std::acos(-1);
}

inline auto update_alfa(double& alfa, const double& delta_time)
{
    constexpr auto speed = 1.5;
    alfa += speed * delta_time;
}

inline auto update_arrows_after_one_turn(double& alfa,
                                         graphics::RendererPool& renderer_pool,
                                         Arrow& arrow,
                                         const double& alfa_of_one_turn,
                                         const double& double_pi)
{
    if (alfa > alfa_of_one_turn)
    {
        alfa -= double_pi;
        renderer_pool.give_back(arrow.back().second);
        arrow.pop_back();
    }
}

inline auto update_events(sf::Window& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

inline auto update_arrow(const double& alfa, Arrow& arrow,
                         graphics::RendererPool& renderer_pool,
                         const graphics::Position& center_position)
{
    auto sinus = std::sin(alfa);
    auto cosinus = std::cos(alfa);

    ranges::for_each(arrow, [&](auto& point) {
        auto new_x = gsl::narrow_cast<float>(point.first * cosinus);
        auto new_y = gsl::narrow_cast<float>(point.first * sinus);

        renderer_pool.set_position(
            point.second, center_position + graphics::Position{new_x, new_y});
    });
}

inline auto
update_time(std::chrono::time_point<std::chrono::system_clock>& last)
{
    const auto now = std::chrono::system_clock::now();
    const auto delta_time = std::chrono::duration<double>(now - last).count();
    last = now;
    return delta_time;
}

int main()
{
    const graphics::WindowSize window_size{800, 600};
    auto renderer_pool = graphics::RendererPoolFactory{}.create(window_size);

    sf::Window window(sf::VideoMode(window_size.width, window_size.height),
                      "My window ");

    const auto center_id = create_object_at_center(window_size, *renderer_pool);
    const auto center_position = renderer_pool->get_position(center_id);

    constexpr auto circle_r = 200;
    constexpr auto step = 40;
    auto arrow = create_arrow_from_point(center_position, circle_r, step,
                                         *renderer_pool);

    const auto pi = calculate_pi();
    const auto double_pi = pi * 2;

    auto alfa = 3*pi/2;
    const auto alfa_of_one_turn = alfa + double_pi;

    auto last = std::chrono::system_clock::now();
    while (window.isOpen() && arrow.size() > 0)
    {
        const auto delta_time = update_time(last);
        update_arrow(alfa, arrow, *renderer_pool, center_position);
        update_alfa(alfa, delta_time);
        update_arrows_after_one_turn(alfa, *renderer_pool, arrow,
                                     alfa_of_one_turn, double_pi);
        renderer_pool->render_all();
        window.display();

        update_events(window);
    }
}
