#ifndef MAINFUNCTIONS_HPP
#define MAINFUNCTIONS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "board.hpp"

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showCheckmatePopup(bool& resetGame, bool& quitGame, bool whitesMove);

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showStaleMatePopup(bool& resetGame, bool& quitGame, bool whitesMove);

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: checkmate is checked for, either showCheckmatePopup is called, or
//		 the game continues
void checkForCheckmate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound);

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: stalemate is checked for, either showStalematePopup is called, or
//		 the game continues
void checkForStalemate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound);

// PRE: font is an sf::Font that determines the styling of the numbers and letters on the rows
//		and columns of the board,
//		squareSize is an int that represents the size of the squares on the board,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
// POST: squares are drawn to the board as well as colored,
//       letters 'a'-'h' are drawn on the bottom row of the board,
//		 numbers 1-7 are drawn on the 1st column of the board
void drawLettersNumbersAndSquares(sf::Font font, int squareSize, sf::RenderWindow& window);

// PRE: window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		clickProcessed is a boolean value asserting that only one click per turn is registered at a time,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		selectedPiece is an sf::Vector2i that represents the square clicked on the board,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		gameState is an int that represents the current state of the game,
//		gameStartSound is an sf::Sound that plays the game-start sound,
//		font is an sf::Font that determines the styling of the numbers and letters on the rows,
//		squareSize is an int that represents the size of the squares on the board
// POST: Pieces are drawn to the window, clicks are processed, as well as checks for checkmate,
//		 stalemate, and draw.
void mainLoop(sf::RenderWindow& window, bool clickProcessed, Board& board, sf::Vector2i selectedPiece, bool whitesMove, int gameState, sf::Sound& gameStartSound, sf::Font font, int squareSize);

#endif