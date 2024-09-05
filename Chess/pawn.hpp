#ifndef PAWN_HPP
#define PAWN_HPP

#include "chessPiece.hpp"

class Pawn : public ChessPiece {
public:
    // Constructors
    Pawn(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Pawn();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const;
    bool canPieceSeeTheKing(Square(&board)[8][8]) const;
    void allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const;
private:
    mutable bool justDoublejumped;
};

#endif