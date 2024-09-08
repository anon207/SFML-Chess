#ifndef MAINFUNCTIONS_HPP
#define MAINFUNCTIONS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "board.hpp"
#include "boardGraphics.hpp"

void showCheckmatePopup(bool& resetGame, bool& quitGame, bool whitesMove);

void showStaleMatePopup(bool& resetGame, bool& quitGame, bool whitesMove);

void checkForCheckmate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound);

void checkForStalemate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound);

void mainLoop(sf::RenderWindow& window, bool clickProcessed, Board& board, sf::Vector2i selectedPiece, bool whitesMove, int gameState, sf::Sound& gameStartSound, sf::Font font, int squareSize);

#endif