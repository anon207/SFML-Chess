#include "bishop.hpp"

// Constructors
Bishop::Bishop(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 7;
	offsetY = 5;
	type = "B";
}

Bishop::~Bishop() {
}

// Public functions
bool Bishop::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// Moving bishop up + left
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

	// Moving bishop up + right
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

	// Moving bishop down + left
	if (moveToPosition.x > position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x && moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x - i][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		return (moveToPosition.x - i == position.x && moveToPosition.y + i == position.y);
	}

	// Moving bishop down + right
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

bool Bishop::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// Check if Bishop can see the king up and to the right
	int i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king up and to the left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king down and to the right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king down and to the left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() != "K") break;
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	return (false);
}