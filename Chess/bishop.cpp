#include "bishop.hpp"

// CONSTRUCTOR
// PRE: pos is the bishops position on the board,
//      col is the bishops color, 
//      spr is the bishops sprite
// POST: Bishop object constructed
Bishop::Bishop(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 7;
	offsetY = 5;
	type = "B";
}

// DESTRUCTOR
// PRE:
// POST:
Bishop::~Bishop() {

}

// PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
//      board is a 8 x 8 matrix of Square objects representing the chess board.
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
// POST: RV = true iff the move is valid or false iff the move is invalid
bool Bishop::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	if (legalMoves["B"].empty()) return (false);

	const std::vector<sf::Vector2i>& bishopMoves = legalMoves["B"];

	auto it = std::find(bishopMoves.begin(), bishopMoves.end(), moveToPosition);

	if (it != bishopMoves.end()) {
		return (true);
	}

	return (false);
}

// PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
// POST: RV is true iff piece can see the opposite color king, or false if piece
//       cannot see the opposite color king
bool Bishop::canPieceSeeTheKing(Square(&board)[8][8]) const {

	// Check if Bishop can see the king up and to the right
	int i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king up and to the left
	i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king down and to the right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != nullptr && otherPiece->getType() != "K") break;
		if (otherPiece != nullptr && otherPiece->getType() == "K" && otherPiece->getColor() != color) return (true);
		i++;
	}
	// Check if Bishop can see the king down and to the left
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
void Bishop::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();

	// all legal moves where Bishop can move up and left
	int i = 1;
	while (position.x - i >= 0 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x - i][position.y - i].GetPiece();
		if (otherPiece != nullptr) {
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

	// all legal moves where Bishop can move up and right
	i = 1;
	while (position.x - i >= 0 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x - i][position.y + i].GetPiece();
		if (otherPiece != nullptr) {
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

	// all legal moves where Bishop can move down and right
	i = 1;
	while (position.x + i <= 7 && position.y + i <= 7) {
		ChessPiece* otherPiece = board[position.x + i][position.y + i].GetPiece();
		if (otherPiece != nullptr) {
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

	// all legal moves where Bishop can move down and left
	i = 1;
	while (position.x + i <= 7 && position.y - i >= 0) {
		ChessPiece* otherPiece = board[position.x + i][position.y - i].GetPiece();
		if (otherPiece != nullptr) {
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