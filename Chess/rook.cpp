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

bool Rook::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	if (legalMoves["R"].empty()) return (false);

	const std::vector<sf::Vector2i>& rookMoves = legalMoves["R"];

	auto it = std::find(rookMoves.begin(), rookMoves.end(), moveToPosition);

	if (it != rookMoves.end()) {
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

void Rook::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();
	
	// all legal moves where rook can move upwards
	int i = 1;
	while (position.x - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y].Clear();
				board[position.x - i][position.y].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y));
				}
				board[position.x - i][position.y].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y].Clear();
		board[position.x - i][position.y].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y));
		}
		i++;
	}
	board[position.x - i + 1][position.y].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where rook can move downwards
	i = 1;
	while (position.x + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y].Clear();
				board[position.x + i][position.y].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y));
				}
				board[position.x + i][position.y].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y].Clear();
		board[position.x + i][position.y].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y));
		}
		i++;
	}
	board[position.x + i - 1][position.y].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where rook can move to the left
	i = 1;
	while (position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x][position.y - i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x][position.y - i + 1].Clear();
				board[position.x][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x, position.y - i));
				}
				board[position.x][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x][position.y - i + 1].Clear();
		board[position.x][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x, position.y - i));
		}
		i++;
	}
	board[position.x][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where rook can move to the right
	i = 1;
	while (position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x][position.y + i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x][position.y + i - 1].Clear();
				board[position.x][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x, position.y + i));
				}
				board[position.x][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x][position.y + i - 1].Clear();
		board[position.x][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x, position.y + i));
		}
		i++;
	}
	board[position.x][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);
}