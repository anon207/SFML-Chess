#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "square.hpp"
#include "board.hpp"
#include <unordered_map>
#include <string>

class ChessPiece {
public:

    // CONSTRUCTOR
    // PRE:
    // POST: ChessPiece object constructed
    ChessPiece();

    // DESTRUCTOR
    // PRE:
    // POST:
    virtual ~ChessPiece();

    // OVERLOADED ASSIGNMENT OPERATOR
    // PRE: other is a valid ChessPiece oject or null
    // POST: position = other.position;
    //       sprite = other.sprite;
    //       color = other.color;
    //       type = other.type;
    //       offsetX = other.offsetX;
    //       offsetY = other.offsetY;
    ChessPiece& operator=(const ChessPiece& other);

    // PRE:
    // POST: RV = piece position
    sf::Vector2i getPosition() const;

    // PRE: 
    // POST: RV = piece sprite
    sf::Sprite& getSprite();

    // PRE:
    // POST: RV = piece type
    std::string getType() const;
    
    // PRE: 
    // POST: RV = piece color 
    char getColor() const;

    // PRE: 
    // POST: RV = piece offsetX
    float getOffsetX() const;

    // PRE: 
    // POST: RV = piece offsetY
    float getOffsetY() const;

    // PRE:
    // POST: RV is true iff the piece has moved or false iff the piece hasnt moved
    bool const getHasMoved() const;

    // PRE:
    // POST: RV = lastMoved
    bool const getLastMoved() const;

    // PRE:
    // POST: RV = justDoubleJumped
    bool getJustDoubleJumped() const;

    // PRE:
    // POST: RV = squaresMoved
    int const getSquaresMoved() const;

    // PRE: pos is defined as an sf::Vector2i
    // POST: position = pos
    void setPosition(const sf::Vector2i& pos);

    // PRE: moved is a boolean value
    // POST: hasMoved = moved
    void setHasMoved(const bool moved);

    // PRE: last is a boolean value
    // POST: lastMoved = last
    void setLastMoved(const bool last);

    // PRE: just is a boolean value
    // POST: justDoubleJumped = just
    void setJustDoubleJumped(const bool just);

    // PRE:
    // POST:
    void setSquaresMoved(const int s);
    
    // PRE: moveToPosition is an sf::Vector2i representing the position the piece is trying to move to
    //      board is a 8 x 8 matrix of Square objects representing the chess board.
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    // POST: RV = true iff the move is valid or false iff the move is invalid
    virtual bool validateMove(const sf::Vector2i& moveToPosition, Square(&board)[8][8], std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves) const = 0;

    // PRE: board is a 8 x 8 matrix of Square objects representing the chess board,
    // POST: RV is true iff piece can see the opposite color king, or false if piece
    //       cannot see the opposite color king
    virtual bool canPieceSeeTheKing(Square(&board)[8][8]) const = 0;

    // PRE: legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      board is a 8 x 8 matrix of Square objects representing the chess board,
    //      whitesMove is a boolean value that is true iff its whites turn or false
    //      iff its blacks turn.
    // POST: legalMoves now contains all the legal moves of the ChessPiece type object.
    virtual void allLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, Square (&board)[8][8], bool whitesMove) const = 0;

    // PRE:
    // POST:
    virtual ChessPiece* clone() const = 0;

protected:

    sf::Vector2i position;
    sf::Sprite sprite;
    std::string type;
    char color;

    // USED FOR CENTERING SPRITES
    float offsetX;
    float offsetY;

    // CASTLING VARIABLE
    bool hasMoved = false;

    // EN PASSANT VARIABLES
    mutable bool lastMoved = false;
    mutable bool justDoubleJumped = false;
    mutable int squaresMoved = 0;
};


#endif 