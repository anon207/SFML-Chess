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
	return (lhs.position == rhs.position &&
		lhs.color == rhs.color &&
		std::string(lhs.type) == std::string(rhs.type));
}

ChessPiece& ChessPiece::operator=(const ChessPiece& other) {
	if (this == &other) return *this;

	position = other.position;
	sprite = other.sprite;
	color = other.color;
	type = other.type;
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

bool const ChessPiece::getLastMoved() const {
	return (lastMoved);
}
void ChessPiece::setLastMoved(const bool last) {
	lastMoved = last;
}

int const ChessPiece::getSquaresMoved() const {
	return (squaresMoved);
}
bool ChessPiece::getJustDoubleJumped() const {
	return (justDoubleJumped);
}

void ChessPiece::setJustDoubleJumped(const bool just) {
	justDoubleJumped = just;
}