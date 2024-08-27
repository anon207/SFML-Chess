#include "Square.hpp"
//#include <cstddef>

Square::Square() {
    piece = nullptr;
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
    piece = nullptr;
}
