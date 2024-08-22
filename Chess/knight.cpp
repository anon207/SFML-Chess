#include "knight.hpp"

// Constructors
Knight::Knight(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = -5;
	offsetY = 4;
	type = "N";
}

Knight::~Knight() {
}

// Public functions
bool Knight::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}