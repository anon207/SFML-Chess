#ifndef BOARD_HPP
#define	BOARD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ChessPiece.hpp"
#include "square.hpp"
#include <unordered_map>
#include <windows.h>
#include <string>

class Board {
public:

    // CONSTRUCTOR
    // PRE: 
    // POST: Board object created and all pieces are initilized on their starting squares.
    Board();

    // DESTRUCTOR
    // PRE: 
    // POST:
    virtual ~Board();

    // Overloading the subscript operator for non-const access
    Square* operator[](int row);

    // Overloading the subscript operator for const access
    const Square* operator[](int row) const;

    // PRE:
    // POST:
    Board& operator=(Board& other);

    // PRE: 
    // POST: All Pieces on board are deleted and re-initilized along with
    //       lastFromPos and lastToPos being reset to (-1, -1).
    void resetBoard();
    
    // PRE: origPiece is a ChessPiece object that could be null, 
    //      whitesMove is a bool that represents whos turn it is, 
    //      fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      window is a sf::RenderWindow which is the window where the board and pieces are displayed,
    //      moveCompleted is a bool that determines whether the move was valid or not,
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      gameState is an int representing the current state of the game
    // POST: white pawn is promoted to one of four pieces- queen, bishop, rook, knight,
    //       or move is invalid.
    bool checkPromotionWhite(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState, bool calledByPlayer);
    
    // PRE: origPiece is a ChessPiece object that could be null, 
    //      whitesMove is a bool that represents whos turn it is, 
    //      fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      window is a sf::RenderWindow which is the window where the board and pieces are displayed,
    //      moveCompleted is a bool that determines whether the move was valid or not,
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      gameState is an int representing the current state of the game
    // POST: Black pawn is promoted to one of four pieces- queen, bishop, rook, knight,
    //       or move is invalid.
    bool checkPromotionBlack(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState, bool calledByPlayer);
    
    // PRE: origPiece is a ChessPiece object that could be null, 
    //      whitesMove is a bool that represents whos turn it is, 
    //      fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      gameState is an int representing the current state of the game
    // POST: White king is either castled king-side or queen side or
    //       Black king is either castled king-side or queen side,
    //       or move is invalid.
    bool checkCastle(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState);
    
    // PRE: origPiece is a ChessPiece object that could be null,
    //      destPiece is a ChessPiece object that could be null, 
    //      whitesMove is a bool that represents whos turn it is, 
    //      fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      gameState is an int representing the current state of the game
    // POST: White pawn captures en passant or Black pawn captures en passant
    //       or move is invalid.
    bool checkEnPassant(ChessPiece* origPiece, ChessPiece* destPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, int& gameState);
    
    // PRE: origPiece is a ChessPiece object that could be null,
    //      destPiece is a ChessPiece object that could be null,
    //      whitesMove is a bool that represents whos turn it is, 
    //      fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      moveCompleted is a bool that determines whether the move was valid or not,
    //      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
    //      gameState is an int representing the current state of the game
    // POST: Move is completed or move is invalid.
    bool checkNormalMove(ChessPiece* origPiece, ChessPiece* destPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, bool& moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState, bool calledByPlayer);
    
    // PRE: fromPos is a sf::Vector2i representing where the piece is moving from,
    //      toPos is a sf::Vector2i representing where the piece is moving to,
    //      whitesMove is a bool that represents whos turn it is, 
    //      window is a sf::RenderWindow which is the window where the board and pieces are displayed,
    //      moveCompleted is a bool that determines whether the move was valid or not,
    //      gameState is an int representing the current state of the game
    // POST: Determines if move is special (castling, en passant, pawn promotion) or normal and whether
    //       or not the move is valid.
    bool MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove, sf::RenderWindow& window, int& gameState, bool calledByPlayer);
    
    // PRE:
    // POST:
    void MovePieceMarkyBot(sf::Vector2i& fromPos, sf::Vector2i toPos, bool whitesMove, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves);

    // PRE:
    // POST: 
    void normalMoveMarkyBot(ChessPiece* piece, ChessPiece* destPiece, bool whitesMove, sf::Vector2i fromPos, sf::Vector2i toPos, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves);

    // PRE: whitesMove is a bool that represents whos turn it is,
    //      board is a reference to the internal state of the Board object
    // POST: determines whether or not the opposite color king is in check
    //       based on whos turn it is.
    static bool isKingInCheck(bool whitesMove, Square(&board)[8][8]);
    
    // PRE: whitesMove is a bool that represents whos turn it is,
    // POST: RV is a hashmap of all legal moves from whoever's turn it is,
    //       keys = piece type, values = vectors of sf::Vector2i's representing valid positions
    //       to move to.
    std::unordered_map<std::string, std::vector<sf::Vector2i>> getLegalMoves(bool whitesMove);

    // PRE:
    // POST:
    void addCastlingToLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, bool whitesMove, int gameState);
    
    // PRE:
    // POST: 
    void addEnPassantToLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, bool whitesMove);

    // PRE: origPiece is a ChessPiece object that is not null,
    // POST: updates the most recently moved piece as the last moved piece
    //       (used for en passant).
    void updateLastMovedPiece(ChessPiece* origPiece);

    // PRE: piecePos is a sf::Vector2i representing the position of the piece being grabbed.
    // POST: RV is pointer to ChessPiece object, can be null or defined.
    ChessPiece* GetPiece(sf::Vector2i piecePos);

    // PRE: mousePosition is a sf::Vector2i representing where on the board a mouse click was registered
    //      windowWidth is an int representing the width of the window.
    // POST: RV is sf::Vector2i representing a square on the board.
    sf::Vector2i GetBoardPosition(const sf::Vector2i& mousePosition, int windowWidth, int windowHeight);

    // PRE: whitesMove is a bool that represents whos turn it is,
    //      gameState is an int representing the current state of the game.
    // POST: RV is either true (Checkmate or check) or false (game in progress).
    bool checkForCheckmate(bool whitesMove, int& gameState, bool insideCheckFunction);

    // PRE: whitesMove is a bool that represents whos turn it is,
    //      gameState is an int representing the current state of the game.
    // POST: RV is either true (stalemate) or false (game in progress).
    bool checkForStalemate(bool whitesMove, int& gameState, bool insideCheckFunction);

    // PRE: whitesMove is a bool that represents whos turn it is,
    //      gameState is an int representing the current state of the game.
    // POST: RV is either true (draw) or false (game in progress).
    bool checkForDrawByInsufficientMaterial(int& gameState, bool insideCheckFunction);

    // PRE:
    // POST: RV = string representing the positions of pieces on the board
    std::string generateBoardState();
    
    // PRE:
    // POST: positionCounts is incremented at the appropriate location matching the board's position
    void updatePositionCounts();

    // PRE: gameState is an int representing the current state of the game.
    // POST: RV is either true (draw) or false (game in progress).
    bool checkForDrawByRepetition(int& gameState, bool insideCheckFunction);

    // PRE: gameState is an int representing the current state of the game.
    // POST: RV is either true (draw) or false (game in progress).
    bool checkForDrawByFiftyMoveRule(int& gameState, bool insideCheckFunction);

    // PRE: window is a sf::RenderWindow which is the window where the board and pieces are displayed,
    // POST: logical display of board is displayed graphically to the window.
    void drawBoard(sf::RenderWindow& window);

    // PRE: board is a Board type object representing the internal state of the board.
    // POST: board's internal state is displayed to the terminal.
    //      (useful for debugging).
    void DisplayBoard(Board board);

    // PRE:
    // POST:
    int evaluateBoard(const Board& board, bool whitesMove);

    // PRE:
    // POST:
    int minimax(Board& board, int depth, bool whitesMove, int alpha, int beta, int gameState, sf::RenderWindow& window);
    
    // PRE:
    // POST:
    void makeBestMove(Board& board, bool &whitesMove, int depth, int gameState, sf::RenderWindow& window, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves);

private:

    // USED TO REPRESENT THE INTERNAL LOGIC OF THE BOARD
    Square board[8][8];

    // USED TO CHECK FOR DRAW BY REPITITION
    std::unordered_map<std::string, int> positionCounts;

    // USED TO CHECK FOR DRAW BY FIFTY MOVE RULE
    int fiftyMoveCounter; 
    
    // PRE:
    // POST: All pieces are placed on their defualt squares and initilized correctly.
    void InitializePieces();

    // PRE: window is an already initialized and open sf::RenderWindow object representing the game window,
    //      transparency is a BYTE value (0-255) representing the desired level of transparency for the window, 
    //      where 0 is fully transparent and 255 is fully opaque.
    // POST: The window's transparency level is set according to transparency,
    //       the window remains functional, continues to render its contents, and responds to user interactions.
    //       the transparency value does not affect the contents within the window, only the window itself, 
    //       making it blend into the desktop with the set transparency.
    void makeWindowTransparent(sf::RenderWindow& window, BYTE transparency);

    // PIECE TEXTURES
    sf::Texture pieceTexture;

    // USED TO HIGHLIGHT SQUARES WHEN A PIECE IS MOVED
    sf::Vector2i lastFromPos;
    sf::Vector2i lastToPos;
    
    // SOUNDS
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

    sf::SoundBuffer china;
    sf::Sound chinaSound;

    sf::SoundBuffer gameEnd;
    sf::Sound gameEndSound;

    sf::SoundBuffer bell;
    sf::Sound bellSound;
};

#endif