#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <cmath>
#include <glm/ext.hpp>
#include <iostream>
#include <memory>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>
#include <vector>

#include "graphics/factory.hpp"
#include "graphics/window.hpp"
#include "math/Position2f.hpp"
#include "math/Size2u.hpp"

class lerp_app
{
public:
    void run()
    {
        while (main_window->is_open())
        {
            calculate_delta_time();
            update_direction_if_key_pressed();
            calculate_traveled_path();
            set_new_position();
            display_frame();
        }
    }

private:
    enum moving_state
    {
        moving_left,
        moving_right,
        moving_up,
        idle
    } current_moving_state{idle};

    void calculate_delta_time()
    {
        auto const now = std::chrono::high_resolution_clock::now();
        delta_time =
            std::chrono::duration<decltype(delta_time)>(now - last_frame)
                .count();
        last_frame = now;
    }

    void calculate_traveled_path()
    {
        percent_of_traveled_path += delta_time * speed;
        if_destination_achieved_stay_idle();
    }

    void recalculate_travel_properties(moving_state const& state,
                                       glm::vec3 const& destination)
    {
        current_moving_state = state;
        destination_position = destination;

        percent_of_traveled_path = 0.0;
        start_position.x = shapes->get_position(box_id).x;
        start_position.y = shapes->get_position(box_id).y;
        auto const one_step =
            1.0f / glm::length(destination_position - start_position);
        speed = static_cast<double>(100 * one_step);
    }

    void update_direction_if_key_pressed()
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

    void if_destination_achieved_stay_idle()
    {
        if (percent_of_traveled_path >= 1.0)
        {
            percent_of_traveled_path = 1.0;
            current_moving_state = idle;
        }
    }

    glm::vec3 lerp(glm::vec3 const& start, glm::vec3 const& end,
                   double const percent)
    {
        return glm::mix(start, end, percent);
    }

    void set_new_position()
    {
        auto const new_position{lerp(start_position, destination_position,
                                     percent_of_traveled_path)};
        shapes->set_position(box_id,
                             math::Position2f{new_position.x, new_position.y});
    }

    void display_frame()
    {
        shapes->render_all();
        main_window->update();
        main_window->display();
    }

    math::Size2f const box_size{15, 15};
    math::Size2u const screen_size{800, 600};
    math::Position2f const screen_center{
        static_cast<float>(screen_size.width) / 2.0f,
        static_cast<float>(screen_size.height) / 2.0f};

    glm::vec3 const left_upper_corner{100, 300, 0};
    glm::vec3 const right_lower_corner{700, 500, 0};
    glm::vec3 const center_upper{400, 100, 0};

    std::unique_ptr<graphics::window> const main_window{
        graphics::create_window(screen_size, "lerp")};
    std::unique_ptr<graphics::renderer_pool> const shapes{
        graphics::create_renderer_pool(screen_size, 600)};

    graphics::renderer_id const left_box_id{shapes->acquire(
        box_size, math::Position2f{left_upper_corner.x, left_upper_corner.y},
        graphics::colors::white)};
    graphics::renderer_id const right_box_id{shapes->acquire(
        box_size, math::Position2f{right_lower_corner.x, right_lower_corner.y},
        graphics::colors::white)};
    graphics::renderer_id const center_box_id{shapes->acquire(
        box_size, math::Position2f{center_upper.x, center_upper.y},
        graphics::colors::white)};
    graphics::renderer_id const box_id{shapes->acquire(
        box_size, math::Position2f{center_upper.x, center_upper.y},
        graphics::colors::green)};

    glm::vec3 start_position{shapes->get_position(box_id).x,
                             shapes->get_position(box_id).y, 0};
    glm::vec3 destination_position = start_position;
    double delta_time = 0.0;
    double percent_of_traveled_path = 0.0;
    double speed = 0.0;
    std::chrono::high_resolution_clock::time_point last_frame{
        std::chrono::high_resolution_clock::now()};
};

int main()
{
    lerp_app{}.run();
}
