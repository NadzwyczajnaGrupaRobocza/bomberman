#include <memory>
#include <cmath>
#include <iostream>
#include <gsl/gsl_util>
#include <chrono>
#include <vector>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>

#include "math/Size2u.hpp"
#include "math/Position2f.hpp"
#include "graphics/factory.hpp"
#include "graphics/window.hpp"

using namespace math;

inline namespace variables
{
struct arrow
{
    int length;
    graphics::renderer_id id;
};

using arrows = std::vector<arrow>;

auto constexpr circle_r = 250;
auto constexpr step = 40;
auto constexpr point_count = circle_r / step;
auto constexpr arrow_size = math::Size2f{20, 30};
auto constexpr available_region = math::Size2u{800, 600};
auto constexpr box_size = math::Size2f{15, 15};
auto constexpr pi = std::acos(-1);
auto constexpr double_pi = pi * 2;
auto constexpr speed = 1.5;

auto const window = graphics::create_window(available_region, "win");
auto const renderer_pool = graphics::create_renderer_pool(available_region);

auto const center_position =
    math::Position2f{static_cast<float>(available_region.width) / 2.0f,
                     static_cast<float>(available_region.height) / 2.0f};
auto const center_point_id =
    renderer_pool
    -> acquire(box_size, center_position, graphics::color{255, 255, 0});

auto alfa = 3 * pi / 2;
auto const alfa_of_one_turn = alfa + double_pi;
auto delta_time = 0.0;
auto clock_arrows = arrows(point_count);
auto last_frame = std::chrono::system_clock::now();
} // namespace variables

inline namespace functions
{
inline auto mark_green_arrow_peak()
{
    if (!clock_arrows.empty())
    {
        renderer_pool->set_color(clock_arrows.back().id,
                                 graphics::colors::green);
    }
}

inline auto create_arrow_from_point()
{
    auto arrow_length = 0;

    ranges::generate(clock_arrows, [&] {
        arrow_length += step;
        return arrow{arrow_length,
                     renderer_pool->acquire(arrow_size, center_position,
                                            graphics::colors::white)};
    });
    mark_green_arrow_peak();
}

inline auto update_arrow_angle()
{
    alfa += speed * delta_time;
}

inline auto update_arrows_after_one_turn()
{
    if (alfa > alfa_of_one_turn)
    {
        alfa -= double_pi;
        renderer_pool->release(clock_arrows.back().id);
        clock_arrows.pop_back();

        mark_green_arrow_peak();
    }
}

inline auto update_arrow_position()
{
    auto sinus = std::sin(alfa);
    auto cosinus = std::cos(alfa);

    ranges::for_each(clock_arrows, [&](auto& arrow) {
        auto new_x = gsl::narrow_cast<float>(arrow.length * cosinus);
        auto new_y = gsl::narrow_cast<float>(arrow.length * sinus);

        renderer_pool->set_position(arrow.id,
                                    center_position + Position2f{new_x, new_y});
    });
}

inline auto calculate_delta_time()
{
    auto const now = std::chrono::system_clock::now();
    delta_time = std::chrono::duration<double>(now - last_frame).count();
    last_frame = now;
}

inline auto display_frame()
{
    renderer_pool->render_all();
    window->display();
    window->update();
}
} // namespace functions

int main()
{
    create_arrow_from_point();

    while (window->is_open() && clock_arrows.size() > 0)
    {
        calculate_delta_time();
        update_arrow_position();
        update_arrow_angle();
        update_arrows_after_one_turn();
        display_frame();
    }
}
