#ifndef ROOK_HPP
#define ROOK_HPP

#include "chessPiece.hpp"

class Rook : public ChessPiece {
public:
    // Constructors
    Rook(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Rook();

    // Public functions
    bool const getHasMoved() const;
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const;
private:
    mutable bool hasMoved;
};

#endif