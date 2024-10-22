#include "chessPiece.hpp"

// CONSTRUCTOR
// PRE:
// POST: ChessPiece object constructed
ChessPiece::ChessPiece() : position(0, 0), color(' '), offsetX(0), offsetY(0), type("") {

}

// DESTRUCTOR
// PRE:
// POST:
ChessPiece::~ChessPiece() {

}

// OVERLOADED ASSIGNMENT OPERATOR
// PRE: other is a valid ChessPiece oject or null
// POST: position = other.position;
//       sprite = other.sprite;
//       color = other.color;
//       type = other.type;
//       offsetX = other.offsetX;
//       offsetY = other.offsetY;
ChessPiece& ChessPiece::operator=(const ChessPiece& other) {
	if (this == &other) return (*this);

	position = other.position;
	sprite = other.sprite;
	color = other.color;
	type = other.type;
	offsetX = other.offsetX;
	offsetY = other.offsetY;

	return (*this);
}

// PRE:
// POST: RV = piece position
sf::Vector2i ChessPiece::getPosition() const {
	return (position);
}

// PRE: 
// POST: RV = piece sprite
sf::Sprite& ChessPiece::getSprite() {
	return (sprite);
}

// PRE:
// POST: RV = piece type
std::string ChessPiece::getType() const {
	return (type);
}

// PRE: 
// POST: RV = piece color 
char ChessPiece::getColor() const {
	return (color);
}

// PRE: 
// POST: RV = piece offsetX
float ChessPiece::getOffsetX() const {
	return (offsetX);
}

// PRE: 
// POST: RV = piece offsetY
float ChessPiece::getOffsetY() const {
	return (offsetY);
}

// PRE:
// POST: RV is true iff the piece has moved or false iff the piece hasnt moved
bool const ChessPiece::getHasMoved() const {
	return (hasMoved);
}

// PRE:
// POST: RV = lastMoved
bool const ChessPiece::getLastMoved() const {
	return (lastMoved);
}

// PRE:
// POST: RV = justDoubleJumped
bool ChessPiece::getJustDoubleJumped() const {
	return (justDoubleJumped);
}

// PRE:
// POST: RV = squaresMoved
int const ChessPiece::getSquaresMoved() const {
	return (squaresMoved);
}

// PRE: pos is defined as an sf::Vector2i
// POST: position = pos
void ChessPiece::setPosition(const sf::Vector2i& pos) {
	position = pos;
}

// PRE: moved is a boolean value
// POST: hasMoved = moved
void ChessPiece::setHasMoved(const bool moved) {
	hasMoved = moved;
}

// PRE: last is a boolean value
// POST: lastMoved = last
void ChessPiece::setLastMoved(const bool last) {
	lastMoved = last;
}

// PRE: just is a boolean value
// POST: justDoubleJumped = just
void ChessPiece::setJustDoubleJumped(const bool just) {
	justDoubleJumped = just;
}

// PRE:
// POST:
void ChessPiece::setSquaresMoved(const int s) {
	squaresMoved = s;
}