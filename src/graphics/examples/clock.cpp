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

class clock_app
{
public:
    clock_app() : clock_arrows(point_count)
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
            update_arrow_angle();
            update_arrows_after_one_turn();
            display_frame();
        }
    }

private:
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

    void update_arrow_angle()
    {
        theta += speed * delta_time;
    }

    void update_arrows_after_one_turn()
    {
        if (theta > angle_after_one_turn)
        {
            theta -= double_pi;
            shapes->release(clock_arrows.back().id);
            clock_arrows.pop_back();

            mark_green_arrow_peak();
        }
    }

    void update_arrow_position()
    {
        auto sinus = std::sin(theta);
        auto cosinus = std::cos(theta);

        ranges::for_each(clock_arrows, [&](auto& clock_arrow) {
            auto new_x = gsl::narrow_cast<float>(clock_arrow.length * cosinus);
            auto new_y = gsl::narrow_cast<float>(clock_arrow.length * sinus);

            shapes->set_position(clock_arrow.id,
                                 center_position +
                                     math::Position2f{new_x, new_y});
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

    double const pi{std::acos(-1)};
    double const double_pi{pi * 2};
    double const speed{1.5};
    std::int32_t const circle_r{250};
    std::int32_t const step{40};
    std::size_t const point_count{static_cast<std::size_t>(circle_r / step)};
    math::Size2f const arrow_size{20, 30};
    math::Size2u const available_region{800, 600};
    math::Size2f const box_size{15, 15};
    math::Position2f const center_position{
        static_cast<float>(available_region.width) / 2.0f,
        static_cast<float>(available_region.height) / 2.0f};

    std::unique_ptr<graphics::window> const main_window =
        graphics::create_window(available_region, "win");
    std::unique_ptr<graphics::renderer_pool> const shapes =
        graphics::create_renderer_pool(available_region);

    double theta = 3 * pi / 2;
    double const angle_after_one_turn = theta + double_pi;
    arrows clock_arrows;
    double delta_time = 0.0;
    std::chrono::high_resolution_clock::time_point last_frame{
        std::chrono::high_resolution_clock::now()};
};

int main()
{
    clock_app{}.run();
}
