#include <chrono>
#include <cmath>
#include <glm/ext.hpp>
#include <gsl/gsl_util>
#include <iostream>
#include <memory>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/generate.hpp>
#include <vector>

#include "graphics/factory.hpp"
#include "graphics/window.hpp"
#include "math/Position2f.hpp"
#include "math/Size2u.hpp"

class slerp_app
{
public:
    slerp_app() : clock_arrows(point_count)
    {
        create_arrow_from_center_point();
        shapes->acquire(box_size, center_position,
                        graphics::color{255, 255, 0});
    }

    void run()
    {
        while (main_window->is_open() && clock_arrows.size() > 0)
        {
            calculate_delta_time();
            update_arrow_position();
            display_frame();
        }
    }

private:
    enum moving_state
    {
        moving_up,
        moving_down,
        moving_left,
        moving_right
    } current_moving_state{moving_right};

    struct arrow
    {
        std::int32_t length;
        graphics::renderer_id id;
    };
    using arrows = std::vector<arrow>;

    void mark_green_arrow_peak()
    {
        if (!clock_arrows.empty())
        {
            shapes->set_color(clock_arrows.back().id, graphics::colors::green);
        }
    }

    void create_arrow_from_center_point()
    {
        auto arrow_length = 0;
        ranges::generate(clock_arrows, [&] {
            arrow_length += step;
            return arrow{arrow_length,
                         shapes->acquire(arrow_size, center_position,
                                         graphics::colors::white)};
        });
        mark_green_arrow_peak();
    }

    glm::vec3 slerp(glm::vec3 const& start, glm::vec3 const& end,
                    float const percent)
    {
        auto const cosinus = glm::clamp(glm::dot(start, end), -1.0f, 1.0f);
        auto const theta = glm::acos(cosinus) * percent;
        auto const relative_direction = glm::normalize(end - start * cosinus);
        return ((start * glm::cos(theta)) +
                (relative_direction * glm::sin(theta)));
    }

    void update_arrow_position()
    {
        auto change = gsl::narrow_cast<float>((1.0 / 1.145) * delta_time);
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

                shapes->release(clock_arrows.back().id);
                clock_arrows.pop_back();
                mark_green_arrow_peak();
                break;
            }
        }

        auto const new_direction =
            slerp(start_direction, destination_direction, travel_path);

        ranges::for_each(clock_arrows, [&](auto& clock_arrow) {
            auto new_position = math::Position2f(
                new_direction.x * static_cast<float>(clock_arrow.length),
                new_direction.y * static_cast<float>(clock_arrow.length));

            shapes->set_position(clock_arrow.id,
                                 center_position + new_position);
        });
    }

    void calculate_delta_time()
    {
        auto const now = std::chrono::high_resolution_clock::now();
        delta_time = std::chrono::duration<double>(now - last_frame).count();
        last_frame = now;
    }

    void display_frame()
    {
        shapes->render_all();
        main_window->display();
        main_window->update();
    }

    std::int32_t const step{40};
    std::int32_t const circle_r{250};
    std::size_t const point_count{static_cast<std::size_t>(circle_r / step)};
    math::Size2f const arrow_size{20, 30};
    math::Size2u const available_region{800, 600};
    math::Size2f const box_size{15, 15};
    glm::vec3 const up_direction{0, -1, 0};
    glm::vec3 const down_direction{0, 1, 0};
    glm::vec3 const right_direction{1, 0, 0};
    glm::vec3 const left_direction{-1, 0, 0};
    math::Position2f const center_position{
        static_cast<float>(available_region.width) / 2.0f,
        static_cast<float>(available_region.height) / 2.0f};

    std::unique_ptr<graphics::window> const main_window =
        graphics::create_window(available_region, "win");
    std::unique_ptr<graphics::renderer_pool> const shapes =
        graphics::create_renderer_pool(available_region, 600);

    arrows clock_arrows;
    float travel_path = 0.0f;
    glm::vec3 start_direction{up_direction};
    glm::vec3 destination_direction{right_direction};
    double delta_time = 0.0;
    std::chrono::high_resolution_clock::time_point last_frame{
        std::chrono::high_resolution_clock::now()};
};

int main()
{
    slerp_app{}.run();
}
