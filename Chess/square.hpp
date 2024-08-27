#ifndef SQUARE_HPP
#define SQUARE_HPP

class ChessPiece;

class Square {
public:
    // Constructors
    Square();
    virtual ~Square();

    // Public functions
    ChessPiece* GetPiece();
    void SetPiece(ChessPiece* piece);
    void Clear();

private:
	ChessPiece* piece;
};

#endif