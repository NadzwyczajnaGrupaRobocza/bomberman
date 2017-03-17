#include "Board.hpp"
#include <iostream>

namespace lmg01
{
Board::Board(const sf::View& initialView) : currentView{initialView},
                                            N{static_cast<int>(currentView.getSize().x / 50.f) + 1},
                                            M{static_cast<int>(currentView.getSize().y / 50.f) + 1}
{
}

void Board::drawOn(sf::RenderTarget& target)
{
    drawEmptyBoard(target);
}

void Board::drawEmptyBoard(sf::RenderTarget& target)
{
    for (auto i = 0; i < N; i++)
    {
        for (auto j = 0; j < M; j++)
        {
            float x_pos = 50.f * static_cast<float>(i);
            float y_pos = 50.f * static_cast<float>(j);
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(x_pos, y_pos);
            target.draw(rectangle);
        }
    }
}

}
