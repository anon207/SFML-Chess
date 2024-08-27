#include "king.hpp"

// Constructors
King::King(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 6;
	offsetY = 4;
	hasMoved = false;
	type = "K";

	moveWhite.loadFromFile("assets/move-self.wav");
	moveWhiteSound.setBuffer(moveWhite);
	moveWhiteSound.setVolume(100);

	moveBlack.loadFromFile("assets/move-opponent.wav");
	moveBlackSound.setBuffer(moveBlack);
	moveBlackSound.setVolume(100);

	castle.loadFromFile("assets/castle.wav");
	castleSound.setBuffer(castle);
	castleSound.setVolume(100);

	capture.loadFromFile("assets/capture.wav");
	captureSound.setBuffer(capture);
	captureSound.setVolume(100);
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
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king down
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y) { 
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king left
	if (moveToPosition.x == position.x && moveToPosition.y == position.y - 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king right
	if (moveToPosition.x == position.x && moveToPosition.y == position.y + 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king up + left
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y - 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king up + right
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y + 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king down + left
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y - 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}
	// Moving king down + right
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y + 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		hasMoved = true;  
		return (true); 
	}

	// Castle king side for white
	if(piece->getColor() == 'W' && 
		hasMoved == false && 
		board[7][7].GetPiece()->getType() == "R" && 
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

		const_cast<sf::Sound&>(castleSound).play();
		
		return (true);
	}

	return (false);
}