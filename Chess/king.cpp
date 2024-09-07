#include "king.hpp"
#include <iostream>

// Constructors
King::King(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 6;
	offsetY = 4;
	hasMoved = false;
	type = "K";
}

King::~King() {
}

// Public functions
bool King::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	if (legalMoves["K"].empty()) return (false);

	const std::vector<sf::Vector2i>& kingMoves = legalMoves["K"];

	auto it = std::find(kingMoves.begin(), kingMoves.end(), moveToPosition);

	if (it != kingMoves.end()) {
		hasMoved = true;
		return (true);
	}

	return (false);
}

bool King::canPieceSeeTheKing(Square(&board)[8][8]) const {
	
	ChessPiece* otherPiece = NULL;

	// Can king see other king above it
	if (position.x != 0) {
		otherPiece = board[position.x - 1][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below it
	if (position.x != 7) {
		otherPiece = board[position.x + 1][position.y].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king to the right of it
	if (position.y != 7) {
		otherPiece = board[position.x][position.y + 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king to the left of it
	if (position.y != 0) {
		otherPiece = board[position.x][position.y - 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king above and right of it
	if (position.x != 0 && position.y != 7) {
		otherPiece = board[position.x - 1][position.y + 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king above and left of it
	if (position.x != 0 && position.y != 0) {
		otherPiece = board[position.x - 1][position.y - 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below and left of it
	if (position.x != 7 && position.y != 0) {
		otherPiece = board[position.x + 1][position.y - 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below and right of it
	if (position.x != 7 && position.y != 0) {
		otherPiece = board[position.x + 1][position.y + 1].GetPiece();
		if (otherPiece != NULL && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}
	
	return (false);
}

void King::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();
	// Moving king up
	if (position.x != 0) {
		ChessPiece* pieceAbove = board[position.x - 1][position.y].GetPiece();
		if (pieceAbove == NULL || (pieceAbove != NULL && pieceAbove->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y].SetPiece(pieceAbove);
		}
	}
	// Moving king down
	if (position.x != 7) {
		ChessPiece* pieceBelow = board[position.x + 1][position.y].GetPiece();
		if (pieceBelow == NULL || (pieceBelow != NULL && pieceBelow->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y].SetPiece(pieceBelow);
		}
	}
	// Moving king left
	if (position.y != 0) {
		ChessPiece* pieceLeft = board[position.x][position.y - 1].GetPiece();
		if (pieceLeft == NULL || (pieceLeft != NULL && pieceLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x][position.y - 1].SetPiece(pieceLeft);
		}
	}
	// Moving king right
	if (position.y != 7) {
		ChessPiece* pieceRight = board[position.x][position.y + 1].GetPiece();
		if (pieceRight == NULL || (pieceRight != NULL && pieceRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x][position.y + 1].SetPiece(pieceRight);
		}
	}
	// Move king up and right
	if (position.x != 0 && position.y != 7) {
		ChessPiece* pieceAboveRight = board[position.x - 1][position.y + 1].GetPiece();
		if (pieceAboveRight == NULL || (pieceAboveRight != NULL && pieceAboveRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y + 1].SetPiece(pieceAboveRight);
		}
	}
	// Move king up and left
	if (position.x != 0 && position.y != 0) {
		ChessPiece* pieceAboveLeft = board[position.x - 1][position.y - 1].GetPiece();
		if (pieceAboveLeft == NULL || (pieceAboveLeft != NULL && pieceAboveLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y - 1].SetPiece(pieceAboveLeft);
		}
	}
	// Move king down and left
	if (position.x != 7 && position.y != 0) {
		ChessPiece* pieceBelowLeft = board[position.x + 1][position.y - 1].GetPiece();
		if (pieceBelowLeft == NULL || (pieceBelowLeft != NULL && pieceBelowLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y - 1].SetPiece(pieceBelowLeft);
		}
	}
	// Move king down and right
	if (position.x != 7 && position.y != 7) {
		ChessPiece* pieceBelowRight = board[position.x + 1][position.y + 1].GetPiece();
		if (pieceBelowRight == NULL || (pieceBelowRight != NULL && pieceBelowRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y + 1].SetPiece(pieceBelowRight);
		}
	}
}