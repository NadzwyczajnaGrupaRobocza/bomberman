#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <gsl/gsl_util>
#include <chrono>

#include "graphics/RendererPoolFactory.hpp"
#include "graphics/Size.hpp"
#include "graphics/WindowSize.hpp"
#include "graphics/Position.hpp"

int main()
{
    const graphics::WindowSize window_size{800, 600};
    auto renderer_pool = graphics::RendererPoolFactory{}.create(window_size);

    sf::Window window(sf::VideoMode(window_size.width, window_size.height),
                      "My window ");

    const auto center_id = renderer_pool->take(
        graphics::Size{15, 15}, graphics::Position{window_size.width / 2.0f,
                                                   window_size.height / 2.0f});

    const auto center = renderer_pool->get_position(center_id);
    const auto r = 200;

    const auto step = 40;
    const auto size = r / step;
    float current_pos = step;

    std::vector<std::pair<int, graphics::RendererId>> points(size);
    std::generate(points.begin(), points.end(), [&] {
        const auto current_r = -current_pos;
        current_pos += step;
        return std::make_pair(
            current_r,
            renderer_pool->take(graphics::Size{20, 30},
                                center + graphics::Position{0.0f, 0.0f}));
    });

    const double pi2 = std::acos(-1) * 2;

    const auto start_alfa = pi2/4;
    const auto end_alfa = start_alfa + pi2;
    auto alfa = start_alfa;

    auto last = std::chrono::system_clock::now();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto now = std::chrono::system_clock::now();
        const auto delta_time =
            std::chrono::duration<double>(now - last).count();
        last = now;

        auto sinus = std::sin(alfa);
        auto cosinus = std::cos(alfa);

        std::for_each(points.begin(), points.end(), [&](auto& point) {
            auto new_x = gsl::narrow_cast<float>(point.first * cosinus);
            auto new_y = gsl::narrow_cast<float>(point.first * sinus);

            renderer_pool->set_position(
                point.second, center + graphics::Position{new_x, new_y});
        });

        const auto speed = 1.5;
        alfa = (alfa + speed * delta_time);
        if (alfa > end_alfa)
        {
            alfa -= pi2;
            renderer_pool->give_back(points.back().second);
            points.pop_back();
            std::clog << "left: " << points.size() << '\n';
        }

        renderer_pool->render_all();
        window.display();

        if (points.size() == 0)
        {
            return 0;
        }
    }
}
