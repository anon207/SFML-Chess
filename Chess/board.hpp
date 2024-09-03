#ifndef BOARD_H
#define	BOARD_H

#include "square.hpp"
#include "ChessPiece.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

class Board {
public:
    // Constructors
    Board();
    virtual ~Board();

    // Public Functions
    bool checkPromotionWhite(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted);
    bool checkPromotionBlack(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted);
    bool checkCastle(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& toPos, sf::Vector2i& fromPos, sf::Vector2i& lastToPos, sf::Vector2i& lastFromPos);
    void updateLastMovedPiece(ChessPiece* origPiece);
    bool MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove, sf::RenderWindow& window);
    ChessPiece* GetPiece(sf::Vector2i piecePos);
    sf::Vector2i GetBoardPosition(const sf::Vector2i& mousePosition, int windowWidth);
    Square(&getBoard())[8][8];
    bool checkEnPassant(ChessPiece* origPiece, ChessPiece* destPiece, sf::Vector2i& toPos, sf::Vector2i& fromPos, bool& whitesMove);
    bool isKingInCheck(bool whitesMove);
    bool checkNormalMove(ChessPiece* origPiece, ChessPiece* destPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, bool& moveCompleted);
    // Graphical board display
    void drawBoard(sf::RenderWindow& window);

    // Debugging function
    void DisplayBoard(Board board);

private:
    // Private Member Variables
    Square board[8][8];

    // Private Member Functions
    void InitializePieces();
    void makeWindowTransparent(sf::RenderWindow& window, BYTE transparency);

    // Piece textures
    sf::Texture pieceTexture;

    // Used to highlight squares when a piece is moved
    sf::Vector2i lastFromPos;
    sf::Vector2i lastToPos;
    
    // Sounds
    sf::SoundBuffer invalidMove;
    sf::Sound invalidMoveSound;

    sf::SoundBuffer promote;
    sf::Sound promoteSound;

    sf::SoundBuffer moveWhite;
    sf::Sound moveWhiteSound;

    sf::SoundBuffer moveBlack;
    sf::Sound moveBlackSound;

    sf::SoundBuffer capture;
    sf::Sound captureSound;

    sf::SoundBuffer castle;
    sf::Sound castleSound;
    
    sf::SoundBuffer check;
    sf::Sound checkSound;
};

#endif