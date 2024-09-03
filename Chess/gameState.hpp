#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "board.hpp"

bool isKingInCheck(Square(&board)[8][8], bool whitesMove); // game continues

bool noLegalMoves(); // game ends

bool isStaleMate(); // game ends

bool isDrawByInsufficientMaterial(); // game ends

bool isDrawByRepition(); // game ends

bool isDrawByFiftyMoveRule(); // game ends

int checkGameState(Square(&board)[8][8], bool whitesMove);

#endif