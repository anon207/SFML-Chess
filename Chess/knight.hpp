#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "chessPiece.hpp"

class Knight : public ChessPiece {
public:
    // Constructors
    Knight(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Knight();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const;
    bool canPieceSeeTheKing(Square(&board)[8][8]) const override;
    void allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const;

};

#endif