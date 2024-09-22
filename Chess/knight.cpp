#include "knight.hpp"

// CONSTRUCTOR
// PRE: pos is the knights position on the board,
//      col is the knights color, 
//      spr is the knights sprite
// POST: Knight object constructed
Knight::Knight(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -5;
	offsetY = 4;
	type = "N";
}

// DESTRUCTOR
// PRE:
// POST:
Knight::~Knight() {

}

// PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
//      board is a 8 x 8 matrix of Square objects representing the chess board.
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
// POST: RV = true iff the move is valid or false iff the move is invalid
bool Knight::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);
	
	if (legalMoves[posKey].empty()) return (false);

	const std::vector<sf::Vector2i>& knightMoves = legalMoves[posKey];

	auto it = std::find(knightMoves.begin(), knightMoves.end(), moveToPosition);

	if (it != knightMoves.end()) {
		return (true);
	}

	return (false);
}

// PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
// POST: RV is true iff piece can see the opposite color king, or false if piece
//       cannot see the opposite color king
bool Knight::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// North East East
	if (position.x + 1 <= 7 && position.y + 2 <= 7 &&
		board[position.x + 1][position.y + 2].GetPiece() != nullptr &&
		board[position.x + 1][position.y + 2].GetPiece()->getType() == "K" &&
		board[position.x + 1][position.y + 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// North West West
	if (position.x + 1 <= 7 && position.y - 2 >= 0 &&
		board[position.x + 1][position.y - 2].GetPiece() != nullptr &&
		board[position.x + 1][position.y - 2].GetPiece()->getType() == "K" &&
		board[position.x + 1][position.y - 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// South East East
	if (position.x - 1 >= 0 && position.y + 2 <= 7 &&
		board[position.x - 1][position.y + 2].GetPiece() != nullptr &&
		board[position.x - 1][position.y + 2].GetPiece()->getType() == "K" &&
		board[position.x - 1][position.y + 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// South West West
	if (position.x - 1 >= 0 && position.y - 2 >= 0 &&
		board[position.x - 1][position.y - 2].GetPiece() != nullptr &&
		board[position.x - 1][position.y - 2].GetPiece()->getType() == "K" &&
		board[position.x - 1][position.y - 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// East North North
	if (position.x + 2 <= 7 && position.y + 1 <= 7 &&
		board[position.x + 2][position.y + 1].GetPiece() != nullptr &&
		board[position.x + 2][position.y + 1].GetPiece()->getType() == "K" &&
		board[position.x + 2][position.y + 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// East South South
	if (position.x - 2 >= 0 && position.y + 1 <= 7 &&
		board[position.x - 2][position.y + 1].GetPiece() != nullptr &&
		board[position.x - 2][position.y + 1].GetPiece()->getType() == "K" &&
		board[position.x - 2][position.y + 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// West North North
	if (position.x + 2 <= 7 && position.y - 1 >= 0 &&
		board[position.x + 2][position.y - 1].GetPiece() != nullptr &&
		board[position.x + 2][position.y - 1].GetPiece()->getType() == "K" &&
		board[position.x + 2][position.y - 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// West South South
	if (position.x - 2 >= 0 && position.y - 1 >= 0 &&
		board[position.x - 2][position.y - 1].GetPiece() != nullptr &&
		board[position.x - 2][position.y - 1].GetPiece()->getType() == "K" &&
		board[position.x - 2][position.y - 1].GetPiece()->getColor() != color) {
		return (true);
	}
	return (false);
}

// PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      board is a 8 x 8 matrix of Square objects representing the chess board,
//      whitesMove is a boolean value that is true iff its whites turn or false
//      iff its blacks turn.
// POST: legalMoves now contains all the legal moves of the ChessPiece type object.
void Knight::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);

	ChessPiece* origPiece = board[position.x][position.y].GetPiece();
	
	// Move Knight North East East
	if (position.x + 1 <= 7 && position.y + 2 <= 7) {
		ChessPiece* otherPiece = board[position.x + 1][position.y + 2].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y + 2].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 1, position.y + 2));
			}
			board[position.x + 1][position.y + 2].Clear();
			board[position.x + 1][position.y + 2].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight North West West
	if (position.x + 1 <= 7 && position.y - 2 >= 0) {
		ChessPiece* otherPiece = board[position.x + 1][position.y - 2].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y - 2].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 1, position.y - 2));
			}
			board[position.x + 1][position.y - 2].Clear();
			board[position.x + 1][position.y - 2].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight South East East
	if (position.x - 1 >= 0 && position.y + 2 <= 7) {
		ChessPiece* otherPiece = board[position.x - 1][position.y + 2].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y + 2].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 1, position.y + 2));
			}
			board[position.x - 1][position.y + 2].Clear();
			board[position.x - 1][position.y + 2].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight South West West
	if (position.x - 1 >= 0 && position.y - 2 >= 0) {
		ChessPiece* otherPiece = board[position.x - 1][position.y - 2].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y - 2].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 1, position.y - 2));
			}
			board[position.x - 1][position.y - 2].Clear();
			board[position.x - 1][position.y - 2].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight East North North
	if (position.x + 2 <= 7 && position.y + 1 <= 7) {
		ChessPiece* otherPiece = board[position.x + 2][position.y + 1].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 2][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 2, position.y + 1));
			}
			board[position.x + 2][position.y + 1].Clear();
			board[position.x + 2][position.y + 1].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight East South South
	if (position.x - 2 >= 0 && position.y + 1 <= 7) {
		ChessPiece* otherPiece = board[position.x - 2][position.y + 1].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 2][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 2, position.y + 1));
			}
			board[position.x - 2][position.y + 1].Clear();
			board[position.x - 2][position.y + 1].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight West North North
	if (position.x + 2 <= 7 && position.y - 1 >= 0) {
		ChessPiece* otherPiece = board[position.x + 2][position.y - 1].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x + 2][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x + 2, position.y - 1));
			}
			board[position.x + 2][position.y - 1].Clear();
			board[position.x + 2][position.y - 1].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	// Move Knight West South South
	if (position.x - 2 >= 0 && position.y - 1 >= 0) {
		ChessPiece* otherPiece = board[position.x - 2][position.y - 1].GetPiece();
		if (otherPiece == nullptr || (otherPiece != nullptr && otherPiece->getColor() != color)) {
			board[position.x][position.y].Clear();
			board[position.x - 2][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[posKey].push_back(sf::Vector2i(position.x - 2, position.y - 1));
			}
			board[position.x - 2][position.y - 1].Clear();
			board[position.x - 2][position.y - 1].SetPiece(otherPiece);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}
}