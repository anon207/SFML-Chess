#ifndef ROOK_HPP
#define ROOK_HPP

#include "chessPiece.hpp"

class Rook : public ChessPiece {
public:
    
    // CONSTRUCTOR
    // PRE: pos is the rooks position on the board,
    //      col is the rooks color, 
    //      spr is the rooks sprite
    // POST: Rook object constructed
    Rook(const sf::Vector2i& pos, char col, const sf::Sprite& spr);

    // DESTRUCTOR
    // PRE:
    // POST:
    virtual ~Rook();

    // PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
    //      board is a 8 x 8 matrix of Square objects representing the chess board.
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    // POST: RV = true iff the move is valid or false iff the move is invalid
    bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const;
    
    // PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
    // POST: RV is true iff piece can see the opposite color king, or false if piece
    //       cannot see the opposite color king
    bool canPieceSeeTheKing(Square(&board)[8][8]) const;

    // PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      board is a 8 x 8 matrix of Square objects representing the chess board,
    //      whitesMove is a boolean value that is true iff its whites turn or false
    //      iff its blacks turn.
    // POST: legalMoves now contains all the legal moves of the ChessPiece type object.
    void allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const;
private:
    
    // VARIABLE USED FOR CASTLING
    mutable bool hasMoved;
};

#endif