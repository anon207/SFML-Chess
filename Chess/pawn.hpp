#ifndef PAWN_HPP
#define PAWN_HPP

#include "chessPiece.hpp"

class Pawn : public ChessPiece {
public:
    // Constructors
    Pawn(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Pawn();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition) const;

private:
    // Indicates whether a double jump first move is available
    bool doubleJumpAvailable;
};

#endif