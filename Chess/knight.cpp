#include "knight.hpp"

// Constructors
Knight::Knight(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -5;
	offsetY = 4;
	type = "N";
}

Knight::~Knight() {
}

// Public functions
bool Knight::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// North East East
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y + 2) return (true);
	
	// North West West
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y - 2) return (true);

	// South East East
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y + 2) return (true);

	// South West West
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y - 2) return (true);

	// East North North
	if (moveToPosition.x == position.x + 2 && moveToPosition.y == position.y + 1) return (true);

	// East South South
	if (moveToPosition.x == position.x - 2 && moveToPosition.y == position.y + 1) return (true);

	// West North North
	if (moveToPosition.x == position.x + 2 && moveToPosition.y == position.y - 1) return (true);

	// West South South
	if (moveToPosition.x == position.x - 2 && moveToPosition.y == position.y - 1) return (true);

	return (false);
}

bool Knight::canPieceSeeTheKing(Square(&board)[8][8]) const {
	// North East East
	if (position.x + 1 <= 7 && position.y + 2 <= 7 &&
		board[position.x + 1][position.y + 2].GetPiece() != NULL &&
		board[position.x + 1][position.y + 2].GetPiece()->getType() == "K" &&
		board[position.x + 1][position.y + 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// North West West
	if (position.x + 1 <= 7 && position.y - 2 >= 0 &&
		board[position.x + 1][position.y - 2].GetPiece() != NULL &&
		board[position.x + 1][position.y - 2].GetPiece()->getType() == "K" &&
		board[position.x + 1][position.y - 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// South East East
	if (position.x - 1 >= 0 && position.y + 2 <= 7 &&
		board[position.x - 1][position.y + 2].GetPiece() != NULL &&
		board[position.x - 1][position.y + 2].GetPiece()->getType() == "K" &&
		board[position.x - 1][position.y + 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// South West West
	if (position.x - 1 >= 0 && position.y - 2 >= 0 &&
		board[position.x - 1][position.y - 2].GetPiece() != NULL &&
		board[position.x - 1][position.y - 2].GetPiece()->getType() == "K" &&
		board[position.x - 1][position.y - 2].GetPiece()->getColor() != color) {
		return (true);
	}
	// East North North
	if (position.x + 2 <= 7 && position.y + 1 <= 7 &&
		board[position.x + 2][position.y + 1].GetPiece() != NULL &&
		board[position.x + 2][position.y + 1].GetPiece()->getType() == "K" &&
		board[position.x + 2][position.y + 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// East South South
	if (position.x - 2 >= 0 && position.y + 1 <= 7 &&
		board[position.x - 2][position.y + 1].GetPiece() != NULL &&
		board[position.x - 2][position.y + 1].GetPiece()->getType() == "K" &&
		board[position.x - 2][position.y + 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// West North North
	if (position.x + 2 <= 7 && position.y - 1 >= 0 &&
		board[position.x + 2][position.y - 1].GetPiece() != NULL &&
		board[position.x + 2][position.y - 1].GetPiece()->getType() == "K" &&
		board[position.x + 2][position.y - 1].GetPiece()->getColor() != color) {
		return (true);
	}
	// West South South
	if (position.x - 2 >= 0 && position.y - 1 >= 0 &&
		board[position.x - 2][position.y - 1].GetPiece() != NULL &&
		board[position.x - 2][position.y - 1].GetPiece()->getType() == "K" &&
		board[position.x - 2][position.y - 1].GetPiece()->getColor() != color) {
		return (true);
	}
	return (false);
}