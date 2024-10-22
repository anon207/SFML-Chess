#ifndef SQUARE_HPP
#define SQUARE_HPP

class ChessPiece;

class Square {
public:
    
    // CONSTRUCTOR
    // PRE:
    // POST: Square object constructed with piece = nullptr
    Square();

    // DESTRUCTOR
    // PRE:
    // POST:        
    virtual ~Square();

    // PRE:
    // POST: RV = piece
    ChessPiece* GetPiece();

    const ChessPiece* GetPiece() const;

    // PRE: piece is a ChessPiece object that is defined or nullptr.
    // POST: piece = p
    void SetPiece(ChessPiece* p);

    // PRE: 
    // POST: piece = nullptr
    void Clear();

private:

    // EACH SQUARE STORES A PIECE
	ChessPiece* piece;
};

#endif