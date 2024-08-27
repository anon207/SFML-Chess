#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "square.hpp"

class ChessPiece {
public:
    // variable used for castling the king.
    bool hasMoved = false;

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
    // sounds
    sf::SoundBuffer moveWhite;
    sf::Sound moveWhiteSound;

    sf::SoundBuffer moveBlack;
    sf::Sound moveBlackSound;

    sf::SoundBuffer castle;
    sf::Sound castleSound;

    sf::SoundBuffer capture;
    sf::Sound captureSound;
};


#endif 