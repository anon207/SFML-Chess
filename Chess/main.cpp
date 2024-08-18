#include <SFML/Graphics.hpp>
#include "boardGraphics.hpp"
#include <iostream>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");

    sf::Texture texture;
    texture.loadFromFile("C:/Users/granb/source/repos/Chess/Chess/assets/chess_pieces.png");

    sf::Font font;
    font.loadFromFile("C:/Users/granb/source/repos/Chess/Chess/assets/RobotoCondensed-Black.ttf");

    const int squareSize = 100;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        drawLettersNumbersAndSquares(font, squareSize, window);
        initPieces(texture, window, squareSize);

        window.display();
    }

    return 0;
}