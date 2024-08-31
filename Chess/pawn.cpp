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

	moveWhite.loadFromFile("assets/move-self.wav");
	moveWhiteSound.setBuffer(moveWhite);
	moveWhiteSound.setVolume(100);

	moveBlack.loadFromFile("assets/move-opponent.wav");
	moveBlackSound.setBuffer(moveBlack);
	moveBlackSound.setVolume(100);

	capture.loadFromFile("assets/capture.wav");
	captureSound.setBuffer(capture);
	captureSound.setVolume(100);
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
		
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		piece->setJustDoubleJumped(true);
		squaresMoved += 2;
		return (true);
	}
	// Moving one square, only valid if pawn is on the same column after move and
	// no piece is at moveToPosition square
	if (moveToPosition.y == position.y &&
		(piece->getColor() == 'W' && moveToPosition.x == position.x - 1 && moveToPosition.y == position.y && otherPiece == nullptr) ||
		(piece->getColor() == 'B' && moveToPosition.x == position.x + 1 && moveToPosition.y == position.y && otherPiece == nullptr)) {
		
		if (piece->getColor() == 'W' && otherPiece == NULL && moveToPosition.x != 0) {
			const_cast<sf::Sound&>(moveWhiteSound).play();
		}
		if (piece->getColor() == 'B' && otherPiece == NULL && moveToPosition.x != 7) {
			const_cast<sf::Sound&>(moveBlackSound).play();
		}

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

		if (piece->getColor() == 'W' && moveToPosition.x != 0) {
			const_cast<sf::Sound&>(captureSound).play();
		}
		if (piece->getColor() == 'B' && moveToPosition.x != 7) {
			const_cast<sf::Sound&>(captureSound).play();
		}

		squaresMoved++;
		return (true);
	}
	
	// En Passant, capturing an opposite color pawn that has just moved two squares and is currently adjacent 
	// to the pawn being moved.
	if (otherPiece == NULL &&
		(piece->getColor() == 'W' &&
		moveToPosition.x == position.x - 1 &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece() != NULL &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece()->getType() == "P" &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece()->getColor() != piece->getColor() &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece()->getLastMoved() == true &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece()->getJustDoubleJumped() &&
		board[moveToPosition.x + 1][moveToPosition.y].GetPiece()->getSquaresMoved() == 2) || 
		(piece->getColor() == 'B' &&
		moveToPosition.x == position.x + 1 &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece() != NULL &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece()->getType() == "P" &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece()->getColor() != piece->getColor() &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece()->getLastMoved() == true &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece()->getJustDoubleJumped() &&
		board[moveToPosition.x - 1][moveToPosition.y].GetPiece()->getSquaresMoved() == 2)) {

		if (piece->getColor() == 'W') board[moveToPosition.x + 1][moveToPosition.y].Clear();

		if (piece->getColor() == 'B') board[moveToPosition.x - 1][moveToPosition.y].Clear();

		board[moveToPosition.x][moveToPosition.y].SetPiece(piece);
		board[piece->getPosition().x][piece->getPosition().y].Clear();
		piece->setPosition(moveToPosition);
		piece->setLastMoved(true);

		const_cast<sf::Sound&>(captureSound).play();
		squaresMoved++;
		return (true);
	}
	return (false);
}