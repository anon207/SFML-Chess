#include "queen.hpp"
#include <iostream>

// Constructors
Queen::Queen(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 1;
	offsetY = 5;
	type = "Q";
}

Queen::~Queen() {
}

// Public functions
bool Queen::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// Moving queen down
	if (moveToPosition.x > position.x && moveToPosition.y == position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x) {
			if (board[moveToPosition.x - i][moveToPosition.y].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (true);
	}

	// Moving queen up
	if (moveToPosition.x < position.x && moveToPosition.y == position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x) {
			if (board[moveToPosition.x + i][moveToPosition.y].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (true);
	}

	// Moving queen left
	if (moveToPosition.x == position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (true);
	}

	// Moving queen right
	if (moveToPosition.x == position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (true);
	}

	// Moving queen up + left
	if (moveToPosition.x < position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x && moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x + i][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (moveToPosition.x + i == position.x && moveToPosition.y + i == position.y);
	}

	// Moving queen up + right
	if (moveToPosition.x < position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x && moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x + i][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (moveToPosition.x + i == position.x && moveToPosition.y - i == position.y);
	}

	// Moving queen down + left
	if (moveToPosition.x > position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x && moveToPosition.y + i < position.y) {
			std::cout << moveToPosition.x - i << std::endl;
			if (board[moveToPosition.x - i][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (moveToPosition.x - i == position.x && moveToPosition.y + i == position.y);
	}

	// Moving queen down + right
	if (moveToPosition.x > position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x && moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x - i][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (moveToPosition.x - i == position.x && moveToPosition.y - i == position.y);
	}

	return (false);
}

bool Queen::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// Check if the Queen can see the king above it
	int i = 1;
	while (position.x - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king below it
	i = 1;
	while (position.x + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king to the left of it
	i = 1;
	while (position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king to the right of it
	i = 1;
	while (position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king up and to the right
	i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king up and to the left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king down and to the right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king down and to the left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	return (false);
}