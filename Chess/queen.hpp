#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "chessPiece.hpp"

class Queen : public ChessPiece {
public:
    // Constructors
    Queen(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Queen();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const;
};

#endif