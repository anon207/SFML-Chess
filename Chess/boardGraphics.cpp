#include "boardGraphics.hpp"
#include <SFML/Graphics.hpp>

void drawLettersNumbersAndSquares(sf::Font font, int squareSize, sf::RenderWindow& window) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);

            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color(227, 237, 246));
            }
            else {
                square.setFillColor(sf::Color(137, 173, 203));
            }

            window.draw(square);
        }
    }

    for (int row = 0; row < 8; ++row) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(8 - row));
        text.setCharacterSize(24);
        if (row % 2 == 0) {
            text.setFillColor(sf::Color(137, 173, 203));
        }
        else {
            text.setFillColor(sf::Color(227, 237, 246));
        }
        text.setPosition(5, row * squareSize);
        window.draw(text);
    }

    for (int col = 0; col < 8; ++col) {
        sf::Text text;
        text.setFont(font);
        text.setString(static_cast<char>('a' + col));
        text.setCharacterSize(24);
        if (col % 2 == 0) {
            text.setFillColor(sf::Color(227, 237, 246));
        }
        else {
            text.setFillColor(sf::Color(137, 173, 203));
        }
        text.setPosition(col * squareSize + 85, 770);
        window.draw(text);
    }
}