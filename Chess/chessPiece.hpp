#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <SFML/Graphics.hpp>

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
    virtual bool validateMove(const sf::Vector2i& moveToPosition) const = 0;

    // Overloaded == operator
    friend bool operator==(const ChessPiece& lhs, const ChessPiece& rhs);
    
    // Overloaded = operator
    ChessPiece& operator=(const ChessPiece& other);

protected:
    sf::Vector2i position;
    sf::Sprite sprite;
    char color;
    std::string type;
    // used for centering sprites in the board sqaures
    float offsetX;
    float offsetY;
};


#endif 