#ifndef BOARD_H
#define	BOARD_H

#include "Square.hpp"
#include "ChessPiece.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Board {
public:
    // Constructors
    Board();
    virtual ~Board();

    // Public Functions
    bool MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove);
    ChessPiece* GetPiece(sf::Vector2i piecePos);
    sf::Vector2i GetBoardPosition(const sf::Vector2i& mousePosition, int windowWidth);
    
    // Graphical board display
    void drawBoard(sf::RenderWindow& window);

    // Debugging function
    void DisplayBoard(Board board);

private:
    // Private Member Variables
    Square board[8][8];
    // Private Member Functions
    void InitializePieces();
    // Piece textures
    sf::Texture pieceTexture;
    // Used to highlight squares when a piece is moved
    sf::Vector2i lastFromPos;
    sf::Vector2i lastToPos;
    // Sounds
    sf::SoundBuffer buffer;
    sf::Sound sound;


};

#endif