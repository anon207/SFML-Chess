#include "Square.hpp"

// CONSTRUCTOR
// PRE:
// POST: Square object constructed with piece = nullptr
Square::Square() {
    piece = nullptr;
}

// DESTRUCTOR
// PRE:
// POST:   
Square::~Square() {

}

// PRE:
// POST: RV = piece
ChessPiece* Square::GetPiece() {
    return (piece);
}

const ChessPiece* Square::GetPiece() const {
    return (piece);
}

// PRE: piece is a ChessPiece object that is defined or nullptr.
// POST: piece = p
void Square::SetPiece(ChessPiece* p) {
    piece = p;
}

// PRE: 
// POST: piece = nullptr
void Square::Clear() {
    piece = nullptr;
}
