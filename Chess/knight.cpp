#include "knight.hpp"

// Constructors
Knight::Knight(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -5;
	offsetY = 4;
	type = "N";

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

Knight::~Knight() {
}

// Public functions
bool Knight::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// North East East
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y + 2) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// North West West
	if (moveToPosition.x == position.x + 1 && moveToPosition.y == position.y - 2) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// South East East
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y + 2) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// South West West
	if (moveToPosition.x == position.x - 1 && moveToPosition.y == position.y - 2) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// East North North
	if (moveToPosition.x == position.x + 2 && moveToPosition.y == position.y + 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// East South South
	if (moveToPosition.x == position.x - 2 && moveToPosition.y == position.y + 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// West North North
	if (moveToPosition.x == position.x + 2 && moveToPosition.y == position.y - 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}
	// West South South
	if (moveToPosition.x == position.x - 2 && moveToPosition.y == position.y - 1) {
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (true);
	}

	return (false);
}