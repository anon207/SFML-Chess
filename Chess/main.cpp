#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "mainFunctions.hpp"
#include "board.hpp"

int main() {
    sf::SoundBuffer gameStart;
    sf::Sound gameStartSound;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chessboard");
    sf::Vector2i selectedPiece(-1, -1);
    sf::Font font;

    font.loadFromFile("assets/RobotoCondensed-Black.ttf");
    gameStart.loadFromFile("assets/game-start.wav");
    gameStartSound.setBuffer(gameStart);
    gameStartSound.setVolume(100);
    gameStartSound.play();

    Board board;

    bool clickProcessed = false;
    bool whitesMove = true;

    int gameState = 0; // 0 == in-progress, 1 == checkMate, 2 == draw, 3 == staleMate
    const int squareSize = 100;

    mainLoop(window, clickProcessed, board, selectedPiece, whitesMove, gameState, gameStartSound, font, squareSize);

    return (0);
}