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
bool King::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor() && otherPiece->getType() != "R") return (false);

	// Moving king up
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king down
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y) { 
		hasMoved = true;  
		return (true); 
	}
	// Moving king left
	if (moveToPosition.x == position.x && moveToPosition.y == position.y - 1) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king right
	if (moveToPosition.x == position.x && moveToPosition.y == position.y + 1) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king up + left
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y - 1) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king up + right
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y + 1) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king down + left
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y - 1) {
		hasMoved = true;  
		return (true); 
	}
	// Moving king down + right
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y + 1) {
		hasMoved = true;  
		return (true); 
	}

	// Castle king side for white
	if(piece->getColor() == 'W' && 
		hasMoved == false && 
		board[7][7].GetPiece() != NULL &&
		board[7][7].GetPiece()->getType() == "R" && 
		board[7][7].GetPiece()->getColor() == 'W' &&
		!board[7][7].GetPiece()->getHasMoved() &&
		board[7][6].GetPiece() == NULL && 
		board[7][5].GetPiece() == NULL &&
		moveToPosition.x == 7 && 
		(moveToPosition.y == 6 || moveToPosition.y == 7)) {

		board[7][5].SetPiece(board[7][7].GetPiece());
		board[7][7].Clear();
		board[7][6].SetPiece(board[7][4].GetPiece());
		board[7][4].Clear();

		board[7][5].GetPiece()->setHasMoved(true);
		board[7][6].GetPiece()->setHasMoved(true);
		board[7][5].GetPiece()->setPosition(sf::Vector2i(7, 5));
		board[7][6].GetPiece()->setPosition(sf::Vector2i(7, 6));
		
		return (true);
	}

	// Castle queen side for white
	if (piece->getColor() == 'W' &&
		hasMoved == false &&
		board[7][0].GetPiece() != NULL &&
		board[7][0].GetPiece()->getType() == "R" &&
		board[7][0].GetPiece()->getColor() == 'W' &&
		!board[7][0].GetPiece()->getHasMoved() &&
		board[7][1].GetPiece() == NULL &&
		board[7][2].GetPiece() == NULL &&
		board[7][3].GetPiece() == NULL &&
		moveToPosition.x == 7 &&
		(moveToPosition.y == 2 || moveToPosition.y == 1 || moveToPosition.y == 0)) {

		board[7][3].SetPiece(board[7][0].GetPiece());
		board[7][0].Clear();
		board[7][2].SetPiece(board[7][4].GetPiece());
		board[7][4].Clear();

		board[7][3].GetPiece()->setHasMoved(true);
		board[7][2].GetPiece()->setHasMoved(true);
		board[7][3].GetPiece()->setPosition(sf::Vector2i(7, 3));
		board[7][2].GetPiece()->setPosition(sf::Vector2i(7, 2));

		return (true);
	}
	
	// Castle king side for Black
	if (piece->getColor() == 'B' &&
		hasMoved == false &&
		board[0][7].GetPiece() != NULL &&
		board[0][7].GetPiece()->getType() == "R" &&
		board[0][7].GetPiece()->getColor() == 'B' &&
		!board[0][7].GetPiece()->getHasMoved() &&
		board[0][6].GetPiece() == NULL &&
		board[0][5].GetPiece() == NULL &&
		moveToPosition.x == 0 &&
		(moveToPosition.y == 6 || moveToPosition.y == 7)) {

		board[0][5].SetPiece(board[0][7].GetPiece());
		board[0][7].Clear();
		board[0][6].SetPiece(board[0][4].GetPiece());
		board[0][4].Clear();

		board[0][5].GetPiece()->setHasMoved(true);
		board[0][6].GetPiece()->setHasMoved(true);
		board[0][5].GetPiece()->setPosition(sf::Vector2i(0, 5));
		board[0][6].GetPiece()->setPosition(sf::Vector2i(0, 6));

		return (true);
	}

	// Castle queen side for black
	if (piece->getColor() == 'B' &&
		hasMoved == false &&
		board[0][0].GetPiece() != NULL &&
		board[0][0].GetPiece()->getType() == "R" &&
		board[0][0].GetPiece()->getColor() == 'B' &&
		!board[0][0].GetPiece()->getHasMoved() &&
		board[0][1].GetPiece() == NULL &&
		board[0][2].GetPiece() == NULL &&
		board[0][3].GetPiece() == NULL &&
		moveToPosition.x == 0 &&
		(moveToPosition.y == 2 || moveToPosition.y == 1 || moveToPosition.y == 0)) {

		board[0][3].SetPiece(board[0][0].GetPiece());
		board[0][0].Clear();
		board[0][2].SetPiece(board[0][4].GetPiece());
		board[0][4].Clear();

		board[0][3].GetPiece()->setHasMoved(true);
		board[0][2].GetPiece()->setHasMoved(true);
		board[0][3].GetPiece()->setPosition(sf::Vector2i(0, 3));
		board[0][2].GetPiece()->setPosition(sf::Vector2i(0, 2));

		return (true);
	}

	return (false);
}

bool King::canPieceSeeTheKing(Square(&board)[8][8]) const {
	return (false);
}