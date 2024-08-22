#include "Square.hpp"
#include "ChessPiece.hpp"

Square::Square() {
    piece = NULL;
}

Square::~Square() {
}

ChessPiece* Square::GetPiece() {
    return (piece);
}

void Square::SetPiece(ChessPiece* p) {
    piece = p;
}

void Square::Clear() {
    piece = NULL;
}

// Overloaded != operator
//bool Square::operator!=(const Square& other) const {
//    return (this->piece != other.piece);
//}
