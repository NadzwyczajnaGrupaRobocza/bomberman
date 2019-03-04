#include <memory>
#include <cmath>
#include <iostream>
#include <gsl/gsl_util>
#include <chrono>
#include <vector>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>
#include <glm/ext.hpp>

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

auto const window = graphics::create_window(available_region, "win");
auto const renderer_pool = graphics::create_renderer_pool(available_region);

auto const center_position =
    math::Position2f{static_cast<float>(available_region.width) / 2.0f,
                     static_cast<float>(available_region.height) / 2.0f};
auto const center_point_id =
    renderer_pool
    -> acquire(box_size, center_position, graphics::color{255, 255, 0});

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

inline auto create_arrow_from_center_point()
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

enum moving_state
{
    moving_up,
    moving_down,
    moving_left,
    moving_right
} current_moving_state{moving_right};

float travel_path = 0.0f;
auto constexpr up_direction = glm::vec3{0, -1, 0};
auto constexpr down_direction = glm::vec3{0, 1, 0};
auto constexpr right_direction = glm::vec3{1, 0, 0};
auto constexpr left_direction = glm::vec3{-1, 0, 0};

auto start_direction{up_direction};
auto destination_direction{right_direction};

inline auto slerp(glm::vec3 const& start, glm::vec3 const& end,
                  const float percent)
{
    auto const dot = glm::clamp(glm::dot(start, end), -1.0f, 1.0f);
    auto const theta = glm::acos(dot) * percent;
    auto const relative_direction = glm::normalize(end - start * dot);
    return ((start * glm::cos(theta)) + (relative_direction * glm::sin(theta)));
}

inline auto update_arrow_position()
{
    auto change = static_cast<float>((1.0 / 1.145) * delta_time);
    travel_path += change;

    if (travel_path >= 1.0f)
    {
        travel_path -= 1.0f;
        switch (current_moving_state)
        {
        case moving_right:
            current_moving_state = moving_down;
            start_direction = right_direction;
            destination_direction = down_direction;
            break;

        case moving_down:
            current_moving_state = moving_left;
            start_direction = down_direction;
            destination_direction = left_direction;
            break;

        case moving_left:
            current_moving_state = moving_up;
            start_direction = left_direction;
            destination_direction = up_direction;
            break;

        case moving_up:
            current_moving_state = moving_right;
            start_direction = up_direction;
            destination_direction = right_direction;

            renderer_pool->release(clock_arrows.back().id);
            clock_arrows.pop_back();
            mark_green_arrow_peak();
            break;
        }
    }

    auto const new_direction =
        slerp(start_direction, destination_direction, travel_path);

    ranges::for_each(clock_arrows, [&](auto& arrow) {
        auto new_position = math::Position2f(
            new_direction.x * static_cast<float>(arrow.length),
            new_direction.y * static_cast<float>(arrow.length));

        renderer_pool->set_position(arrow.id, center_position + new_position);
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
    create_arrow_from_center_point();

    while (window->is_open() && clock_arrows.size() > 0)
    {
        calculate_delta_time();
        update_arrow_position();
        display_frame();
    }
}
