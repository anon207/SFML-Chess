#include "gameState.hpp"


bool isKingInCheck(Square(&board)[8][8], bool whitesMove) {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			ChessPiece* piece = board[row][col].GetPiece();
			if (piece != NULL && piece->getColor() == 'B' && whitesMove) {
				if (piece->canPieceSeeTheKing(board)) return (true);
			}
			if (piece != NULL && piece->getColor() == 'W' && !whitesMove) {
				if (piece->canPieceSeeTheKing(board)) return (true);
			}
		}
	}
	return (false);
}

bool noLegalMoves() {
	// if this function is entered that means one of the two kings is either in check or checkmate.
	return (true);
}

bool isStaleMate() {

	return (false);
}

bool isDrawByInsufficientMaterial() {
	return (false);
}

bool isDrawByRepition() {
	// use hashmap- key: square[8][8], value: how many times that board has appeared.
	return (false);
}

bool isDrawByFiftyMoveRule() {
	return (false);
}

int checkGameState(Square(&board)[8][8], bool whitesMove) {
	// 0 == game is in progress
	// 1 == king is in check
	// 2 == king is in checkmate
	// 3 == draw
	// 4 == stalemate
	if (isKingInCheck(board, whitesMove)) {
		if (noLegalMoves()) {
			// Play checkmate sound
			return (2);
		}
		// Play check sound
		return (1);
	}
	else {
		if (isDrawByInsufficientMaterial() || isDrawByRepition() || isDrawByFiftyMoveRule()) return (3);
		if (isStaleMate()) return (4);
	}
	return (0);
}