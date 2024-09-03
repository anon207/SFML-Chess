#include "pawn.hpp"
#include <iostream>

// Constructors
Pawn::Pawn(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -25.5;
	offsetY = 0;
	type = "P";
	justDoublejumped = false;
}

Pawn::~Pawn() {
}

// Public functions
bool Pawn::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// Moving two squares, only valid if pawn is on the same column after move
	// white pawn on row 6 or black pawn on row 1 and no piece is at moveToPosition square
	if (moveToPosition.y == position.y && 
		(piece->getColor() == 'W'  && position.x == 6 && moveToPosition.x == position.x - 2 && otherPiece == nullptr) ||
		(piece->getColor() == 'B' && position.x == 1 && moveToPosition.x == position.x + 2) && otherPiece == nullptr) {
		
		piece->setJustDoubleJumped(true);
		squaresMoved += 2;
		return (true);
	}
	// Moving one square, only valid if pawn is on the same column after move and
	// no piece is at moveToPosition square
	if (moveToPosition.y == position.y &&
		(piece->getColor() == 'W' && moveToPosition.x == position.x - 1 && moveToPosition.y == position.y && otherPiece == nullptr) ||
		(piece->getColor() == 'B' && moveToPosition.x == position.x + 1 && moveToPosition.y == position.y && otherPiece == nullptr)) {
		
		squaresMoved++;
		return (true);
	}
	// capturing a piece, only valid if there is a piece at moveToPosition square,
	// if pawn is white, moveToPosition square can either be in the column to the left or right of the
	// initial column the move is started from and the row above or below depending on the piece color.
	if (otherPiece != NULL &&
		((piece->getColor() == 'W' && moveToPosition.x == position.x - 1 &&
		(moveToPosition.y == position.y - 1 || moveToPosition.y == position.y + 1)) ||
		(piece->getColor() == 'B' && moveToPosition.x == position.x + 1 &&
		(moveToPosition.y == position.y - 1 || moveToPosition.y == position.y + 1)))) {

		squaresMoved++;
		return (true);
	}
	return (false);
}

bool Pawn::canPieceSeeTheKing(Square(&board)[8][8]) const {
	if (color == 'W') {
		ChessPiece* upRight = board[position.x - 1][position.y + 1].GetPiece();
		ChessPiece* upLeft = board[position.x - 1][position.y - 1].GetPiece();
		if ((upRight != NULL &&
			upRight->getType() == "K" &&
			upRight->getColor() != color) ||
			(upLeft != NULL &&
				upLeft->getType() == "K" &&
				upLeft->getColor() != color)) {
			return (true);
		}
	}
	if (color == 'B') {
		ChessPiece* upRight = board[position.x + 1][position.y + 1].GetPiece();
		ChessPiece* upLeft = board[position.x + 1][position.y - 1].GetPiece();
		if ((upRight != NULL &&
			upRight->getType() == "K" &&
			upRight->getColor() != color) ||
			(upLeft != NULL &&
				upLeft->getType() == "K" &&
				upLeft->getColor() != color)) {
			return (true);
		}
	}
	return (false);
}