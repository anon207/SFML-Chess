#include "rook.hpp"
#include <iostream>

// Constructors
Rook::Rook(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -16.5;
	offsetY = 3;
	hasMoved = false;
	type = "R";
}

Rook::~Rook() {
}

// Public functions
bool const Rook::getHasMoved() const {
	return (hasMoved);
}

bool Rook::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();
	
	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// Moving rook down
	if (moveToPosition.x > position.x && moveToPosition.y == position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x) {
			if (board[moveToPosition.x - i][moveToPosition.y].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		hasMoved = true;
		return (true);
	}

	// Moving rook up
	if (moveToPosition.x < position.x && moveToPosition.y == position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x) {
			if (board[moveToPosition.x + i][moveToPosition.y].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		hasMoved = true;
		return (true);
	}

	// Moving rook left
	if (moveToPosition.x == position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		hasMoved = true;
		return (true);
	}

	// Moving rook right
	if (moveToPosition.x == position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		hasMoved = true;
		return (true);
	}

	return (false);
}

bool Rook::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// Check if the Rook can see the king above it
	int i = 1;
	while (position.x - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		std::cout << position.x - i << " " << std::endl;
		i++;
	}
	// Check if the Rook can see the king below it
	i = 1;
	while (position.x + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Rook can see the king to the left of it
	i = 1;
	while (position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Rook can see the king to the right of it
	i = 1;
	while (position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	return (false);
}