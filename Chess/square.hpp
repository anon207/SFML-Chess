#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "chessPiece.hpp"

class Square {
public:
    // Constructors
    Square();
    virtual ~Square();

    // Public functions
    ChessPiece* GetPiece();
    void SetPiece(ChessPiece* piece);
    void Clear();

    // Overloaded != operator
    /*bool operator!=(const Square& other) const;*/

private:
	ChessPiece* piece;
};

#endif