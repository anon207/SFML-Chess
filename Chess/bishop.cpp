#include "bishop.hpp"

// Constructors
Bishop::Bishop(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 7;
	offsetY = 5;
	type = "B";

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

Bishop::~Bishop() {
}

// Public functions
bool Bishop::validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const {
	ChessPiece* piece = board[position.x][position.y].GetPiece();
	ChessPiece* otherPiece = board[moveToPosition.x][moveToPosition.y].GetPiece();

	// Cant take same color piece
	if (otherPiece != NULL && otherPiece->getColor() == piece->getColor()) return (false);

	// Moving bishop up + left
	if (moveToPosition.x < position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x && moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x + i][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (moveToPosition.x + i == position.x && moveToPosition.y + i == position.y);
	}

	// Moving bishop up + right
	if (moveToPosition.x < position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.x + i < position.x && moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x + i][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (moveToPosition.x + i == position.x && moveToPosition.y - i == position.y);
	}

	// Moving bishop down + left
	if (moveToPosition.x > position.x && moveToPosition.y < position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x && moveToPosition.y + i < position.y) {
			if (board[moveToPosition.x - i][moveToPosition.y + i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (moveToPosition.x - i == position.x && moveToPosition.y + i == position.y);
	}

	// Moving bishop down + right
	if (moveToPosition.x > position.x && moveToPosition.y > position.y) {
		int i = 1;
		while (moveToPosition.x - i > position.x && moveToPosition.y - i > position.y) {
			if (board[moveToPosition.x - i][moveToPosition.y - i].GetPiece() != NULL) {
				return (false);
			}
			i++;
		}
		if (piece->getColor() == 'W' && otherPiece == NULL) const_cast<sf::Sound&>(moveWhiteSound).play();
		if (piece->getColor() == 'B' && otherPiece == NULL) const_cast<sf::Sound&>(moveBlackSound).play();
		if (otherPiece != NULL) const_cast<sf::Sound&>(captureSound).play();
		return (moveToPosition.x - i == position.x && moveToPosition.y - i == position.y);
	}

	return (false);
}