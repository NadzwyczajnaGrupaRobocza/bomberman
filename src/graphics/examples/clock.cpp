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
using arrow = std::vector<std::pair<int, graphics::renderer_id>>;

auto constexpr circle_r = 250;
auto constexpr step = 40;
auto constexpr point_count = circle_r / step;
auto constexpr available_region = math::Size2u{800, 600};
auto constexpr box_size = math::Size2f{15, 15};
auto constexpr pi = std::acos(-1);
auto constexpr double_pi = pi * 2;

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
auto clock_arrow = arrow(point_count);
auto last_frame = std::chrono::system_clock::now();
} // namespace variables

inline namespace functions
{
inline auto mark_green_arrow_peak()
{
    if (!clock_arrow.empty())
    {
        renderer_pool->set_color(clock_arrow.back().second,
                                 graphics::colors::green);
    }
}

inline auto create_arrow_from_point()
{
    float current_pos = static_cast<float>(step);

    ranges::generate(clock_arrow, [&] {
        auto const distance_from_center = current_pos;
        current_pos += static_cast<float>(step);
        return std::make_pair(distance_from_center,
                              renderer_pool->acquire(math::Size2f{20, 30},
                                                     center_position,
                                                     graphics::colors::white));
    });
    mark_green_arrow_peak();
}

inline auto update_angle()
{
    auto constexpr speed = 1.5;
    alfa += speed * delta_time;
}

inline auto update_arrows_after_one_turn()
{
    if (alfa > alfa_of_one_turn)
    {
        alfa -= double_pi;
        renderer_pool->release(clock_arrow.back().second);
        clock_arrow.pop_back();

        mark_green_arrow_peak();
    }
}

inline auto update_arrow()
{
    auto sinus = std::sin(alfa);
    auto cosinus = std::cos(alfa);

    ranges::for_each(clock_arrow, [&](auto& point) {
        auto new_x = gsl::narrow_cast<float>(point.first * cosinus);
        auto new_y = gsl::narrow_cast<float>(point.first * sinus);

        renderer_pool->set_position(point.second,
                                    center_position + Position2f{new_x, new_y});
    });
}

inline auto calculate_delta_time()
{
    auto const now = std::chrono::system_clock::now();
    delta_time = std::chrono::duration<double>(now - last_frame).count();
    last_frame = now;
}
} // namespace functions

int main()
{
    create_arrow_from_point();

    while (window->is_open() && clock_arrow.size() > 0)
    {
        calculate_delta_time();
        update_arrow();
        update_angle();
        update_arrows_after_one_turn();
        renderer_pool->render_all();
        window->display();
        window->update();
    }
}
