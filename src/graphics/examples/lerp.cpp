#include <memory>
#include <cmath>
#include <iostream>
#include <gsl/gsl_util>
#include <chrono>
#include <vector>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>
#include <glm/ext.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "math/Size2u.hpp"
#include "math/Position2f.hpp"
#include "graphics/factory.hpp"
#include "graphics/window.hpp"

inline namespace variables
{
enum moving_state
{
    moving_left,
    moving_right,
    moving_up,
    idle
} current_moving_state{idle};

auto constexpr box_size = math::Size2f{15, 15};
auto constexpr screen_size = math::Size2u{800, 600};
auto constexpr screen_center =
    math::Position2f{static_cast<float>(screen_size.width) / 2.0f,
                     static_cast<float>(screen_size.height) / 2.0f};

auto constexpr left_upper_corner = glm::vec3{100, 300, 0};
auto constexpr right_lower_corner = glm::vec3{700, 500, 0};
auto constexpr center_upper = glm::vec3{400, 100, 0};

auto const window = graphics::create_window(screen_size, "win");
auto const renderer_pool = graphics::create_renderer_pool(screen_size);

auto const left_box_id =
    renderer_pool -> acquire(
        box_size, math::Position2f{left_upper_corner.x, left_upper_corner.y},
        graphics::colors::white);
auto const right_box_id =
    renderer_pool -> acquire(
        box_size, math::Position2f{right_lower_corner.x, right_lower_corner.y},
        graphics::colors::white);
auto const center_box_id =
    renderer_pool
    -> acquire(box_size, math::Position2f{center_upper.x, center_upper.y},
               graphics::colors::white);
auto const box_id =
    renderer_pool
    -> acquire(box_size, math::Position2f{center_upper.x, center_upper.y},
               graphics::colors::green);

auto start_position = glm::vec3{renderer_pool->get_position(box_id).x,
                                renderer_pool->get_position(box_id).y, 0};
auto destination_position = start_position;
auto percent_of_traveled_path = 0.0;
auto speed = 0.0;
auto delta_time = 0.0;
auto last_frame = std::chrono::system_clock::now();

} // namespace variables

inline namespace functions
{
inline auto calculate_delta_time()
{
    auto const now = std::chrono::system_clock::now();
    delta_time = std::chrono::duration<double>(now - last_frame).count();
    last_frame = now;
}

inline auto recalculate_travel_properties(moving_state const& state,
                                          glm::vec3 const& destination)
{
    current_moving_state = state;
    destination_position = destination;

    percent_of_traveled_path = 0.0;
    start_position.x = renderer_pool->get_position(box_id).x;
    start_position.y = renderer_pool->get_position(box_id).y;
    auto const one_step =
        1.0 / glm::length(destination_position - start_position);
    speed = 100 * one_step;
}

inline auto update_direction_if_key_pressed()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        current_moving_state != moving_left)
    {
        recalculate_travel_properties(moving_left, left_upper_corner);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
             current_moving_state != moving_right)
    {
        recalculate_travel_properties(moving_right, right_lower_corner);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
             current_moving_state != moving_up)
    {
        recalculate_travel_properties(moving_up, center_upper);
    }
}

inline auto if_destination_achieved_stay_idle()
{
    if (percent_of_traveled_path >= 1.0)
    {
        percent_of_traveled_path = 1.0;
        current_moving_state = idle;
    }
}

inline auto calculate_traveled_path()
{
    percent_of_traveled_path += delta_time * speed;
    if_destination_achieved_stay_idle();
}

inline auto lerp(glm::vec3 const& start, glm::vec3 const& end,
                 double const percent)
{
    return glm::mix(start, end, percent);
}

inline auto set_new_position()
{
    auto const new_position{
        lerp(start_position, destination_position, percent_of_traveled_path)};
    renderer_pool->set_position(
        box_id, math::Position2f{new_position.x, new_position.y});
}

inline auto display_frame()
{
    renderer_pool->render_all();
    window->display();
    window->update();
}
}

int main()
{
    while (window->is_open())
    {
        calculate_delta_time();
        update_direction_if_key_pressed();
        calculate_traveled_path();
        set_new_position();
        display_frame();
    }
}
