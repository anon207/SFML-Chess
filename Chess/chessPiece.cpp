#include "chessPiece.hpp"

ChessPiece::ChessPiece() : position(0, 0), color(' ') {
}

ChessPiece::~ChessPiece() {
}

sf::Vector2i ChessPiece::getPosition() const {
	return (position);
}

void ChessPiece::setPosition(const sf::Vector2i& pos) {
	position = pos;
}

char ChessPiece::getColor() const {
	return (color);
}
