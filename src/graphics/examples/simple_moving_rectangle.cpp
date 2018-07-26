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
using arrow = std::vector<std::pair<int, graphics::renderer_id>>;

inline auto create_object_at_center(const Size2u& available_region,
                                    graphics::renderer_pool& renderer_pool)
{
    using namespace graphics;
    return renderer_pool.acquire(
        Size2f{15, 15},
        Position2f{static_cast<float>(available_region.width) / 2.0f,
                   static_cast<float>(available_region.height) / 2.0f});
}

inline auto create_arrow_from_point(const Position2f& point,
                                    const std::uint32_t& arrow_length,
                                    const std::uint32_t& arrow_body_density,
                                    graphics::renderer_pool& renderer_pool)
{
    using namespace graphics;
    const auto point_count = arrow_length / arrow_body_density;
    float current_pos = static_cast<float>(arrow_body_density);

    arrow arr(point_count);
    ranges::generate(arr, [&] {
        const auto distance_from_center = current_pos;
        current_pos += static_cast<float>(arrow_body_density);
        return std::make_pair(distance_from_center,
                              renderer_pool.acquire(Size2f{20, 30}, point));
    });
    return arr;
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
                                         graphics::renderer_pool& renderer_pool,
                                         arrow& clock_arrow,
                                         const double& alfa_of_one_turn,
                                         const double& double_pi)
{
    if (alfa > alfa_of_one_turn)
    {
        alfa -= double_pi;
        renderer_pool.release(clock_arrow.back().second);
        clock_arrow.pop_back();
    }
}

inline auto update_arrow(const double& alfa, arrow& clock_arrow,
                         graphics::renderer_pool& renderer_pool,
                         const Position2f& center_position)
{
    auto sinus = std::sin(alfa);
    auto cosinus = std::cos(alfa);

    ranges::for_each(clock_arrow, [&](auto& point) {
        auto new_x = gsl::narrow_cast<float>(point.first * cosinus);
        auto new_y = gsl::narrow_cast<float>(point.first * sinus);

        renderer_pool.set_position(point.second,
                                   center_position + Position2f{new_x, new_y});
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
    const Size2u available_region{800, 600};
    auto window = graphics::create_window(available_region, "win");
    auto renderer_pool = graphics::create_renderer_pool(available_region);

    const auto center_id =
        create_object_at_center(available_region, *renderer_pool);
    const auto center_position = renderer_pool->get_position(center_id);

    constexpr auto circle_r = 200;
    constexpr auto step = 40;
    auto clock_arrow  = create_arrow_from_point(center_position, circle_r, step,
                                         *renderer_pool);

    const auto pi = calculate_pi();
    const auto double_pi = pi * 2;

    auto alfa = 3 * pi / 2;
    const auto alfa_of_one_turn = alfa + double_pi;

    auto last = std::chrono::system_clock::now();
    while (window->is_open() && clock_arrow.size() > 0)
    {
        const auto delta_time = update_time(last);
        update_arrow(alfa, clock_arrow, *renderer_pool, center_position);
        update_alfa(alfa, delta_time);
        update_arrows_after_one_turn(alfa, *renderer_pool, clock_arrow,
                                     alfa_of_one_turn, double_pi);
        renderer_pool->render_all();
        window->display();
        window->update();
    }
}
