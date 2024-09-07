#include <SFML/Graphics.hpp>
#include "boardGraphics.hpp"
#include "chessPiece.hpp"
#include <iostream>
#include "board.hpp"
#include <fstream>
#include <SFML/Audio.hpp>

int main() {
    sf::SoundBuffer gameStart;
    sf::Sound gameStartSound;
    gameStart.loadFromFile("assets/game-start.wav");
    gameStartSound.setBuffer(gameStart);
    gameStartSound.setVolume(100);
    gameStartSound.play();

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");

    Board board;

    bool whitesMove = true;

    // 0 == in-progress, 1 == checkMate, 2 == draw, 3 == staleMate
    int gameState = 0;

    sf::Font font;
    font.loadFromFile("assets/RobotoCondensed-Black.ttf");

    const int squareSize = 100;

    sf::Vector2i selectedPiece(-1, -1);
    bool clickProcessed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || gameState != 0) {
                if (gameState == 1) {
                    std::cout << "CHECKMATE" << std::endl;
                }
                window.close();
            }

            if (!clickProcessed && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2i boardPosition = board.GetBoardPosition(mousePosition, window.getSize().x);

                    if (selectedPiece.x == -1 && selectedPiece.y == -1) {
                        // First click: Select piece
                        if (board.GetPiece(boardPosition) != NULL) {
                            selectedPiece = boardPosition;
                        }
                    }
                    else {
                        // Second click: Attempt to move the piece
                        if (board.MovePiece(selectedPiece, boardPosition, whitesMove, window, gameState)) {
                            selectedPiece = sf::Vector2i(-1, -1); // Reset selection after move
                        }
                    }
                    clickProcessed = true;
                    board.DisplayBoard(board);
                }
            }
        }
        clickProcessed = false;

        drawLettersNumbersAndSquares(font, squareSize, window);
        board.drawBoard(window);

        window.display();
    }

    return 0;
}