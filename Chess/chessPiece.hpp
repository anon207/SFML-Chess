#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "square.hpp"

class ChessPiece {
public:
    // Constructors
    ChessPiece();
    virtual ~ChessPiece();

    // Public functions
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i& pos);
    char getColor() const;
    sf::Sprite& getSprite();
    float getOffsetX() const;
    float getOffsetY() const;
    std::string getType() const;
    virtual bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8]) const = 0;
    bool const getHasMoved() const;
    void setHasMoved(const bool moved);
    bool const getLastMoved() const;
    void setLastMoved(const bool last);
    int const getSquaresMoved() const;
    bool getJustDoubleJumped() const;
    void setJustDoubleJumped(const bool just);
    virtual bool canPieceSeeTheKing(Square(&board)[8][8]) const = 0;

    // Overloaded == operator
    friend bool operator==(const ChessPiece& lhs, const ChessPiece& rhs);
    
    // Overloaded = operator
    ChessPiece& operator=(const ChessPiece& other);

protected:
    sf::Vector2i position;
    sf::Sprite sprite;
    std::string type;
    char color;

    // used for centering sprites in the board sqaures
    float offsetX;
    float offsetY;

    // variable used for castling the king.
    bool hasMoved = false;

    // variables for en passant
    mutable bool lastMoved = false;
    mutable bool justDoubleJumped = false;
    mutable int squaresMoved = 0;
    

};


#endif 