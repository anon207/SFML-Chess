#include "king.hpp"

// Constructors
King::King(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 6;
	offsetY = 4;
	type = "K";
}

King::~King() {
}

// Public functions
bool King::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}