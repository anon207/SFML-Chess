#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "chessPiece.hpp"

class Queen : public ChessPiece {
public:
    // Constructors
    Queen(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    virtual ~Queen();

    // Public functions
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const;
    bool canPieceSeeTheKing(Square(&board)[8][8]) const override;
    void allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const;
};

#endif