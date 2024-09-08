#include "pawn.hpp"

// CONSTRUCTOR
// PRE: pos is the pawns position on the board,
//      col is the pawns color, 
//      spr is the pawns sprite
// POST: Pawn object constructed
Pawn::Pawn(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -25.5;
	offsetY = 0;
	type = "P";
	justDoublejumped = false;
}

// DESTRUCTOR
// PRE:
// POST:
Pawn::~Pawn() {

}

// PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
//      board is a 8 x 8 matrix of Square objects representing the chess board.
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
// POST: RV = true iff the move is valid or false iff the move is invalid
bool Pawn::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const {
	
	if (legalMoves["P"].empty()) return (false);

	const std::vector<sf::Vector2i>& pawnMoves = legalMoves["P"];

	auto it = std::find(pawnMoves.begin(), pawnMoves.end(), moveToPosition);

	if (it != pawnMoves.end()) {
		// Check for double jump
		if (color == 'W' && position.x == moveToPosition.x + 2) {
			ChessPiece* piece = board[position.x][position.y].GetPiece();
			piece->setJustDoubleJumped(true);
			squaresMoved += 2;
		}else if (color == 'B' && position.x == moveToPosition.x - 2) {
			ChessPiece* piece = board[position.x][position.y].GetPiece();
			piece->setJustDoubleJumped(true);
			squaresMoved += 2;
		}
		else {
			squaresMoved++;
		}
		return (true);
	}

	return (false);
}

// PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
// POST: RV is true iff piece can see the opposite color king, or false if piece
//       cannot see the opposite color king
bool Pawn::canPieceSeeTheKing(Square(&board)[8][8]) const {
	if (color == 'W') {
		if ((position.x != 0 && position.y != 7 && 
			board[position.x - 1][position.y + 1].GetPiece() != nullptr &&
			board[position.x - 1][position.y + 1].GetPiece()->getType() == "K" &&
			board[position.x - 1][position.y + 1].GetPiece()->getColor() != color) ||
			(position.x != 0 && position.y != 0 && 
				board[position.x - 1][position.y - 1].GetPiece() != nullptr &&
				board[position.x - 1][position.y - 1].GetPiece()->getType() == "K" &&
				board[position.x - 1][position.y - 1].GetPiece()->getColor() != color)) {
			return (true);
		}
	}
	if (color == 'B') {
		if ((position.x != 7 && position.y != 7 && 
			board[position.x + 1][position.y + 1].GetPiece() != nullptr &&
			board[position.x + 1][position.y + 1].GetPiece()->getType() == "K" &&
			board[position.x + 1][position.y + 1].GetPiece()->getColor() != color) ||
			(position.x != 7 && position.y != 0 &&
				board[position.x + 1][position.y - 1].GetPiece() != nullptr &&
				board[position.x + 1][position.y - 1].GetPiece()->getType() == "K" &&
				board[position.x + 1][position.y - 1].GetPiece()->getColor() != color)) {
			return (true);
		}
	}
	return (false);
}

// PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      board is a 8 x 8 matrix of Square objects representing the chess board,
//      whitesMove is a boolean value that is true iff its whites turn or false
//      iff its blacks turn.
// POST: legalMoves now contains all the legal moves of the ChessPiece type object.
void Pawn::allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const {
	ChessPiece* origPiece = board[position.x][position.y].GetPiece();
	
	if (color == 'W') {
		ChessPiece* pieceAbove = board[position.x - 1][position.y].GetPiece();
		
		// Moving the pawn up one square
		if (pieceAbove == nullptr) {
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y));
			}
			board[position.x - 1][position.y].Clear();
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Moving the pawn up two squares
		if (position.x == 6 && pieceAbove == nullptr && board[position.x - 2][position.y].GetPiece() == nullptr) {
			board[position.x][position.y].Clear();
			board[position.x - 2][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 2, position.y));
			}
			board[position.x - 2][position.y].Clear();
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Capturing a piece above and to the left
		if (position.y != 0 && board[position.x - 1][position.y - 1].GetPiece() != nullptr && board[position.x - 1][position.y - 1].GetPiece()->getColor() != color) {
			ChessPiece* pieceAboveLeft = board[position.x - 1][position.y - 1].GetPiece();
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y - 1].Clear();
			board[position.x - 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y - 1));
			}
			board[position.x - 1][position.y - 1].Clear();
			board[position.x - 1][position.y - 1].SetPiece(pieceAboveLeft);
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Capturing a piece above and to the right
		if (position.y != 7 && board[position.x - 1][position.y + 1].GetPiece() != nullptr && board[position.x - 1][position.y + 1].GetPiece()->getColor() != color) {
			ChessPiece* pieceAboveRight = board[position.x - 1][position.y + 1].GetPiece();
			board[position.x][position.y].Clear();
			board[position.x - 1][position.y + 1].Clear();
			board[position.x - 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x - 1, position.y + 1));
			}
			board[position.x - 1][position.y + 1].Clear();
			board[position.x - 1][position.y + 1].SetPiece(pieceAboveRight);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}

	if (color == 'B') {
		ChessPiece* pieceAbove = board[position.x + 1][position.y].GetPiece();
		
		// Moving the pawn up one square
		if (pieceAbove == nullptr) {
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y));
			}
			board[position.x + 1][position.y].Clear();
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Moving the pawn up two squares
		if (position.x == 1 && pieceAbove == nullptr && board[position.x + 2][position.y].GetPiece() == nullptr) {
			board[position.x][position.y].Clear();
			board[position.x + 2][position.y].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 2, position.y));
			}
			board[position.x + 2][position.y].Clear();
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Capturing a piece above and to the left
		if (position.y != 0 && board[position.x + 1][position.y - 1].GetPiece() != nullptr && board[position.x + 1][position.y - 1].GetPiece()->getColor() != color) {
			ChessPiece* pieceAboveLeft = board[position.x + 1][position.y - 1].GetPiece();
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y - 1].Clear();
			board[position.x + 1][position.y - 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y - 1));
			}
			board[position.x + 1][position.y - 1].Clear();
			board[position.x + 1][position.y - 1].SetPiece(pieceAboveLeft);
			board[position.x][position.y].SetPiece(origPiece);
		}
		// Capturing a piece above and to the right
		if (position.y != 7 && board[position.x + 1][position.y + 1].GetPiece() != nullptr && board[position.x + 1][position.y + 1].GetPiece()->getColor() != color) {
			ChessPiece* pieceAboveRight = board[position.x + 1][position.y + 1].GetPiece();
			board[position.x][position.y].Clear();
			board[position.x + 1][position.y + 1].Clear();
			board[position.x + 1][position.y + 1].SetPiece(origPiece);
			if (!Board::isKingInCheck(!whitesMove, board)) {
				legalMoves[type].push_back(sf::Vector2i(position.x + 1, position.y + 1));
			}
			board[position.x + 1][position.y + 1].Clear();
			board[position.x + 1][position.y + 1].SetPiece(pieceAboveRight);
			board[position.x][position.y].SetPiece(origPiece);
		}
	}
}