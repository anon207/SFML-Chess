#include "queen.hpp"

// CONSTRUCTOR
// PRE: pos is the queens position on the board,
//      col is the queens color, 
//      spr is the queens sprite
// POST: Queen object constructed
Queen::Queen(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 1;
	offsetY = 5;
	type = "Q";
}

// DESTRUCTOR
// PRE:
// POST:
Queen::~Queen() {

}

// PRE:
// POST:
ChessPiece* Queen::clone() const {
	return new Queen(*this);
}

// PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
//      board is a 8 x 8 matrix of Square objects representing the chess board.
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
// POST: RV = true iff the move is valid or false iff the move is invalid
bool Queen::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);

	if (legalMoves[posKey].empty()) return (false);

	const std::vector<sf::Vector2i>& queenMoves = legalMoves[posKey];

	auto it = std::find(queenMoves.begin(), queenMoves.end(), moveToPosition);

	if (it != queenMoves.end()) return (true);

	return (false);
}

// PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
// POST: RV is true iff piece can see the opposite color king, or false if piece
//       cannot see the opposite color king
bool Queen::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// Check if the Queen can see the king above it
	int i = 1;
	while (position.x - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king below it
	i = 1;
	while (position.x + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king to the left of it
	i = 1;
	while (position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x][position.y - i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if the Queen can see the king to the right of it
	i = 1;
	while (position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x][position.y + i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king up and to the right
	i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king up and to the left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king down and to the right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Queen can see the king down and to the left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	return (false);
}

// PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      board is a 8 x 8 matrix of Square objects representing the chess board,
//      whitesMove is a boolean value that is true iff its whites turn or false
//      iff its blacks turn.
// POST: legalMoves now contains all the legal moves of the ChessPiece type object.
void Queen::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	
	std::string posKey = type + std::to_string(position.x) + std::to_string(position.y);
	
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();

	// all legal moves where Queen can move upwards
	int i = 1;
	while (position.x - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y].Clear();
				board[position.x - i][position.y].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y));
				}
				board[position.x - i][position.y].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y].Clear();
		board[position.x - i][position.y].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y));
		}
		i++;
	}
	board[position.x - i + 1][position.y].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move downwards
	i = 1;
	while (position.x + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y].Clear();
				board[position.x + i][position.y].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y));
				}
				board[position.x + i][position.y].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y].Clear();
		board[position.x + i][position.y].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y));
		}
		i++;
	}
	board[position.x + i - 1][position.y].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move to the left
	i = 1;
	while (position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x][position.y - i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x][position.y - i + 1].Clear();
				board[position.x][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y - i));
				}
				board[position.x][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x][position.y - i + 1].Clear();
		board[position.x][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y - i));
		}
		i++;
	}
	board[position.x][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move to the right
	i = 1;
	while (position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x][position.y + i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x][position.y + i - 1].Clear();
				board[position.x][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y + i));
				}
				board[position.x][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x][position.y + i - 1].Clear();
		board[position.x][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x, position.y + i));
		}
		i++;
	}
	board[position.x][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move up and left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y - i + 1].Clear();
				board[position.x - i][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y - i));
				}
				board[position.x - i][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y - i + 1].Clear();
		board[position.x - i][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y - i));
		}
		i++;
	}
	board[position.x - i + 1][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move up and right
	i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x - i + 1][position.y + i - 1].Clear();
				board[position.x - i][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y + i));
				}
				board[position.x - i][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x - i + 1][position.y + i - 1].Clear();
		board[position.x - i][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x - i, position.y + i));
		}
		i++;
	}
	board[position.x - i + 1][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move down and right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y + i - 1].Clear();
				board[position.x + i][position.y + i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y + i));
				}
				board[position.x + i][position.y + i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y + i - 1].Clear();
		board[position.x + i][position.y + i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y + i));
		}
		i++;
	}
	board[position.x + i - 1][position.y + i - 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);

	// all legal moves where Queen can move down and left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != nullptr) {
			if (otherPiece->getColor() != color) {
				board[position.x + i - 1][position.y - i + 1].Clear();
				board[position.x + i][position.y - i].SetPiece(origPiece);
				if (!Board::isKingInCheck(!whitesMove, board)) {
					legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y - i));
				}
				board[position.x + i][position.y - i].SetPiece(otherPiece);
			}
			break;
		}
		board[position.x + i - 1][position.y - i + 1].Clear();
		board[position.x + i][position.y - i].SetPiece(origPiece);
		// check if same color king is in check after making a move
		if (!Board::isKingInCheck(!whitesMove, board)) {
			legalMoves[posKey].push_back(sf::Vector2i(position.x + i, position.y - i));
		}
		i++;
	}
	board[position.x + i - 1][position.y - i + 1].Clear();
	board[position.x][position.y].SetPiece(origPiece);
}