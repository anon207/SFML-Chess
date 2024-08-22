#include "bishop.hpp"

// Constructors
Bishop::Bishop(const sf::Vector2i& pos, char col, const sf::Sprite& spr) {
	position = pos;
	color = col;
	sprite = spr;
	offsetX = 7;
	offsetY = 5;
	type = "B";
}

Bishop::~Bishop() {
}

// Public functions
bool Bishop::validateMove(const sf::Vector2i& moveToPosition) const {
	return (true);
}