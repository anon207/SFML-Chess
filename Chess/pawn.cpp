#include "pawn.hpp"

// Constructors
Pawn::Pawn(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	doubleJumpAvailable = true;
	offsetX = -25.5;
	offsetY = 0;
	type = "P";
}

Pawn::~Pawn() {
}

// Public functions
bool Pawn::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}