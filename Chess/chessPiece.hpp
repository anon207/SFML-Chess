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
    virtual bool validateMove(const sf::Vector2i& moveToPosition) const = 0;

protected:
    sf::Vector2i position;
    sf::Sprite sprite;
    char color;
};


#endif 