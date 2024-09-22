#include "king.hpp"

// CONSTRUCTOR
// PRE: pos is the kings position on the board,
//      col is the kings color, 
//      spr is the kings sprite
// POST: King object constructed
King::King(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 6;
	offsetY = 4;
	hasMoved = false;
	type = "K";
}

// DESTRUCTOR
// PRE:
// POST:
King::~King() {

}

// PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
//      board is a 8 x 8 matrix of Square objects representing the chess board.
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
// POST: RV = true iff the move is valid or false iff the move is invalid
bool King::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);

	if (legalMoves[posKey].empty()) return (false);

	const std::vector<sf::Vector2i>& kingMoves = legalMoves[posKey];

	auto it = std::find(kingMoves.begin(), kingMoves.end(), moveToPosition);

	if (it != kingMoves.end()) {
		board[position.x][position.y].GetPiece()->setHasMoved(true);
		return (true);
	}

	return (false);
}

// PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
// POST: RV is true iff piece can see the opposite color king, or false if piece
//       cannot see the opposite color king
bool King::canPieceSeeTheKing(Square(&board)[8][8]) const {
	
	ChessPiece* otherPiece = nullptr;

	// Can king see other king above it
	if (position.x != 0) {
		otherPiece = board[position.x - 1][position.y].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below it
	if (position.x != 7) {
		otherPiece = board[position.x + 1][position.y].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king to the right of it
	if (position.y != 7) {
		otherPiece = board[position.x][position.y + 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king to the left of it
	if (position.y != 0) {
		otherPiece = board[position.x][position.y - 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king above and right of it
	if (position.x != 0 && position.y != 7) {
		otherPiece = board[position.x - 1][position.y + 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king above and left of it
	if (position.x != 0 && position.y != 0) {
		otherPiece = board[position.x - 1][position.y - 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below and left of it
	if (position.x != 7 && position.y != 0) {
		otherPiece = board[position.x + 1][position.y - 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}

	// Can king see other king below and right of it
	if (position.x != 7 && position.y != 7) {
		otherPiece = board[position.x + 1][position.y + 1].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
	}
	
	return (false);
}

// PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      board is a 8 x 8 matrix of Square objects representing the chess board,
//      whitesMove is a boolean value that is true iff its whites turn or false
//      iff its blacks turn.
// POST: legalMoves now contains all the legal moves of the ChessPiece type object.
void King::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);

	ChessPiece* origPiece = board[position.x][position.y].GetPiece();
	
	// Moving king up
	if (position.x != 0) {
		ChessPiece* pieceAbove = board[position.x - 1][position.y].GetPiece();
		if (pieceAbove == nullptr || (pieceAbove != nullptr && pieceAbove->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 1, position.y));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y].SetPiece(pieceAbove);
		}
	}
	// Moving king down
	if (position.x != 7) {
		ChessPiece* pieceBelow = board[position.x + 1][position.y].GetPiece();
		if (pieceBelow == nullptr || (pieceBelow != nullptr && pieceBelow->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 1, position.y));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y].SetPiece(pieceBelow);
		}
	}
	// Moving king left
	if (position.y != 0) {
		ChessPiece* pieceLeft = board[position.x][position.y - 1].GetPiece();
		if (pieceLeft == nullptr || (pieceLeft != nullptr && pieceLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x][position.y - 1].SetPiece(pieceLeft);
		}
	}
	// Moving king right
	if (position.y != 7) {
		ChessPiece* pieceRight = board[position.x][position.y + 1].GetPiece();
		if (pieceRight == nullptr || (pieceRight != nullptr && pieceRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x][position.y + 1].SetPiece(pieceRight);
		}
	}
	// Move king up and right
	if (position.x != 0 && position.y != 7) {
		ChessPiece* pieceAboveRight = board[position.x - 1][position.y + 1].GetPiece();
		if (pieceAboveRight == nullptr || (pieceAboveRight != nullptr && pieceAboveRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 1, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y + 1].SetPiece(pieceAboveRight);
		}
	}
	// Move king up and left
	if (position.x != 0 && position.y != 0) {
		ChessPiece* pieceAboveLeft = board[position.x - 1][position.y - 1].GetPiece();
		if (pieceAboveLeft == nullptr || (pieceAboveLeft != nullptr && pieceAboveLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 1, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x - 1][position.y - 1].SetPiece(pieceAboveLeft);
		}
	}
	// Move king down and left
	if (position.x != 7 && position.y != 0) {
		ChessPiece* pieceBelowLeft = board[position.x + 1][position.y - 1].GetPiece();
		if (pieceBelowLeft == nullptr || (pieceBelowLeft != nullptr && pieceBelowLeft->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 1, position.y - 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y - 1].SetPiece(pieceBelowLeft);
		}
	}
	// Move king down and right
	if (position.x != 7 && position.y != 7) {
		ChessPiece* pieceBelowRight = board[position.x + 1][position.y + 1].GetPiece();
		if (pieceBelowRight == nullptr || (pieceBelowRight != nullptr && pieceBelowRight->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 1, position.y + 1));
			}
			board[position.x][position.y].SetPiece(origPiece);
			board[position.x + 1][position.y + 1].SetPiece(pieceBelowRight);
		}
	}
}