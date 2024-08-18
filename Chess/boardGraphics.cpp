#include "boardGraphics.hpp"
#include <SFML/Graphics.hpp>

void initPieces(sf::Texture texture, sf::RenderWindow& window, int squareSize) {
    // White pawns
    sf::Sprite WhitePawnSprite;
    WhitePawnSprite.setTexture(texture);
    WhitePawnSprite.setTextureRect(sf::IntRect(1571, 0, 314, 270));
    WhitePawnSprite.setScale(0.34f, 0.34f);
    drawPiece(WhitePawnSprite, 6, 0, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 1, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 2, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 3, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 4, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 5, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 6, -25.5, 0, window, squareSize);
    drawPiece(WhitePawnSprite, 6, 7, -25.5, 0, window, squareSize);
    // Black pawns
    sf::Sprite BlackPawnSprite;
    BlackPawnSprite.setTexture(texture);
    BlackPawnSprite.setTextureRect(sf::IntRect(1571, 335, 314, 270));
    BlackPawnSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackPawnSprite, 1, 0, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 1, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 2, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 3, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 4, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 5, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 6, -25.5, 0, window, squareSize);
    drawPiece(BlackPawnSprite, 1, 7, -25.5, 0, window, squareSize);
    // White rooks
    sf::Sprite WhiteRookSprite;
    WhiteRookSprite.setTexture(texture);
    WhiteRookSprite.setTextureRect(sf::IntRect(1270, 0, 314, 270));
    WhiteRookSprite.setScale(0.34f, 0.34f);
    drawPiece(WhiteRookSprite, 7, 0, -16.5, 3, window, squareSize);
    drawPiece(WhiteRookSprite, 7, 7, -16.5, 3, window, squareSize);
    // Black rooks
    sf::Sprite BlackRookSprite;
    BlackRookSprite.setTexture(texture);
    BlackRookSprite.setTextureRect(sf::IntRect(1270, 335, 314, 270));
    BlackRookSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackRookSprite, 0, 0, -16.5, 3, window, squareSize);
    drawPiece(BlackRookSprite, 0, 7, -16.5, 3, window, squareSize);
    // White knights
    sf::Sprite WhiteKnightSprite;
    WhiteKnightSprite.setTexture(texture);
    WhiteKnightSprite.setTextureRect(sf::IntRect(970, 0, 314, 270));
    WhiteKnightSprite.setScale(0.34f, 0.34f);
    drawPiece(WhiteKnightSprite, 7, 1, -5, 4, window, squareSize);
    drawPiece(WhiteKnightSprite, 7, 6, -5, 4, window, squareSize);
    // Black Knights
    sf::Sprite BlackKnightSprite;
    BlackKnightSprite.setTexture(texture);
    BlackKnightSprite.setTextureRect(sf::IntRect(970, 335, 314, 270));
    BlackKnightSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackKnightSprite, 0, 1, -5, 4, window, squareSize);
    drawPiece(BlackKnightSprite, 0, 6, -5, 4, window, squareSize);
    // White Bishops
    sf::Sprite WhiteBishopSprite;
    WhiteBishopSprite.setTexture(texture);
    WhiteBishopSprite.setTextureRect(sf::IntRect(670, 0, 314, 270));
    WhiteBishopSprite.setScale(0.34f, 0.34f);
    drawPiece(WhiteBishopSprite, 7, 2, 7, 5, window, squareSize);
    drawPiece(WhiteBishopSprite, 7, 5, 7, 5, window, squareSize);
    // Black Bishops
    sf::Sprite BlackBishopSprite;
    BlackBishopSprite.setTexture(texture);
    BlackBishopSprite.setTextureRect(sf::IntRect(670, 335, 314, 270));
    BlackBishopSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackBishopSprite, 0, 2, 7, 5, window, squareSize);
    drawPiece(BlackBishopSprite, 0, 5, 7, 5, window, squareSize);
    // White Queen
    sf::Sprite WhiteQueenSprite;
    WhiteQueenSprite.setTexture(texture);
    WhiteQueenSprite.setTextureRect(sf::IntRect(320, 0, 340, 270));
    WhiteQueenSprite.setScale(0.34f, 0.34f);
    drawPiece(WhiteQueenSprite, 7, 3, 1, 5, window, squareSize);
    // Black Queen
    sf::Sprite BlackQueenSprite;
    BlackQueenSprite.setTexture(texture);
    BlackQueenSprite.setTextureRect(sf::IntRect(320, 335, 340, 270));
    BlackQueenSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackQueenSprite, 0, 3, 1, 5, window, squareSize);
    // White King
    sf::Sprite WhiteKingSprite;
    WhiteKingSprite.setTexture(texture);
    WhiteKingSprite.setTextureRect(sf::IntRect(0, 0, 314, 270));
    WhiteKingSprite.setScale(0.34f, 0.34f);
    drawPiece(WhiteKingSprite, 7, 4, 6, 4, window, squareSize);
    // Black King
    sf::Sprite BlackKingSprite;
    BlackKingSprite.setTexture(texture);
    BlackKingSprite.setTextureRect(sf::IntRect(0, 335, 314, 270));
    BlackKingSprite.setScale(0.34f, 0.34f);
    drawPiece(BlackKingSprite, 0, 4, 6, 4, window, squareSize);
}

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

void drawPiece(sf::Sprite piece, int row, int col, int offsetX, int offsetY, sf::RenderWindow& window, int squareSize) {
    piece.setPosition((col * squareSize) + offsetX, (row * squareSize) + offsetY);
    window.draw(piece);
}