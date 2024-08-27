#include "chessPiece.hpp"

ChessPiece::ChessPiece() : position(0, 0), color(' '), offsetX(0), offsetY(0), type("") {
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
sf::Sprite& ChessPiece::getSprite() {
	return (sprite);
}

float ChessPiece::getOffsetX() const {
	return (offsetX);
}

float ChessPiece::getOffsetY() const {
	return (offsetY);
}

std::string ChessPiece::getType() const {
	return (type);
}

bool operator==(const ChessPiece& lhs, const ChessPiece& rhs) {
	//sf::Vector2i pos(lhs.position.y, lhs.position.x);
	return (lhs.position == rhs.position &&
		lhs.color == rhs.color &&
		std::string(lhs.type) == std::string(rhs.type));
}

ChessPiece& ChessPiece::operator=(const ChessPiece& other) {
	if (this == &other) return *this; // Self-assignment check

	// Copy the attributes
	position = other.position;
	sprite = other.sprite;
	color = other.color;
	type = other.type; // No need for manual memory management with std::string
	offsetX = other.offsetX;
	offsetY = other.offsetY;

	return *this;
}

bool const ChessPiece::getHasMoved() const {
	return (hasMoved);
}

void ChessPiece::setHasMoved(const bool moved) {
	hasMoved = moved;
}