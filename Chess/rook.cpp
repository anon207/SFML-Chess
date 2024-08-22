#include "rook.hpp"

// Constructors
Rook::Rook(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -16.5;
	offsetY = 3;
	type = "R";
}

Rook::~Rook() {
}

// Public functions
bool Rook::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}