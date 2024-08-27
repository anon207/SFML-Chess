#ifndef KING_HPP
#define KING_HPP

#include "chessPiece.hpp"

class King : public ChessPiece {
public:
    // Constructors
    King(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~King();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const;
    
private:
    mutable bool hasMoved;
};

#endif