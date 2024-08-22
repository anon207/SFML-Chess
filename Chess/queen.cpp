#include "queen.hpp"

// Constructors
Queen::Queen(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 1;
	offsetY = 5;
	type = "Q";
}

Queen::~Queen() {
}

// Public functions
bool Queen::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}