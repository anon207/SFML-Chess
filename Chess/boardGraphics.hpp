#ifndef BOARD_GRAPHICS_HPP
#define BOARD_GRAPHICS_HPP

#include <SFML/Graphics.hpp>

void initPieces(sf::Texture texture, sf::RenderWindow& window, int squareSize);
void drawLettersNumbersAndSquares(sf::Font font, int squareSize, sf::RenderWindow& window);
void drawPiece(sf::Sprite piece, int row, int col, int offsetX, int offsetY, sf::RenderWindow& window, int squareSize);

#endif
