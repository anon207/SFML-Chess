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
bool Queen::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	if (legalMoves["Q"].empty()) return (false);

	const std::vector<sf::Vector2i>& queenMoves = legalMoves["Q"];

	auto it = std::find(queenMoves.begin(), queenMoves.end(), moveToPosition);

	if (it != queenMoves.end()) return (true);

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

void Queen::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();

	// all legal moves where Queen can move upwards
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

	// all legal moves where Queen can move downwards
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

	// all legal moves where Queen can move to the left
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

	// all legal moves where Queen can move to the right
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

	// all legal moves where Queen can move up and left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y - i + 1].Clear();
				board[position.x - i][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y - i));
				}
				board[position.x - i][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y - i + 1].Clear();
		board[position.x - i][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y - i));
		}
		i++;
	}
	board[position.x - i + 1][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move up and right
	i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y + i - 1].Clear();
				board[position.x - i][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y + i));
				}
				board[position.x - i][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y + i - 1].Clear();
		board[position.x - i][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x - i, position.y + i));
		}
		i++;
	}
	board[position.x - i + 1][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move down and right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y + i - 1].Clear();
				board[position.x + i][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y + i));
				}
				board[position.x + i][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y + i - 1].Clear();
		board[position.x + i][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y + i));
		}
		i++;
	}
	board[position.x + i - 1][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move down and left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != NULL) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y - i + 1].Clear();
				board[position.x + i][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y - i));
				}
				board[position.x + i][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y - i + 1].Clear();
		board[position.x + i][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[type].push_back(sf::Vector2i(position.x + i, position.y - i));
		}
		i++;
	}
	board[position.x + i - 1][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);
}