#include "board.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"
#include <iostream>

Board::Board() : lastFromPos(-1, -1), lastToPos(-1, -1) {
    buffer.loadFromFile("C:/Users/granb/source/repos/Chess/Chess/move-self.wav");
    sound.setBuffer(buffer);
    sound.setVolume(50);
    InitializePieces();
}

Board::~Board() {
}

bool Board::MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove) {

    bool moveCompleted = false;

    ChessPiece* origPiece = board[fromPos.x][fromPos.y].GetPiece();

    if (origPiece != NULL && ((origPiece->getColor() == 'W' && whitesMove == true) || ((origPiece->getColor() == 'B' && whitesMove == false))) && origPiece->validateMove(toPos) && fromPos != toPos) {
        origPiece->setPosition(toPos);
        if (board[toPos.x][toPos.y].GetPiece() != NULL) {
            board[toPos.x][toPos.y].Clear();
        }
        else {

        }
        board[toPos.x][toPos.y].SetPiece(origPiece);
        board[fromPos.x][fromPos.y].Clear();

        lastFromPos = fromPos;
        lastToPos = toPos;

        moveCompleted = true;
        whitesMove = !whitesMove;
    }
    sound.play();
    if (!moveCompleted) {
        fromPos = sf::Vector2i(-1, -1);
    }

    return (moveCompleted);
}

ChessPiece* Board::GetPiece(sf::Vector2i piecePos) {
    return board[piecePos.x][piecePos.y].GetPiece();
}

void Board::InitializePieces() {
    // Load texture
    pieceTexture.loadFromFile("C:/Users/granb/source/repos/Chess/Chess/assets/chess_pieces.png");
    
    // Initialize Pawns
    sf::Sprite WhitePawnSprite;
    WhitePawnSprite.setTexture(pieceTexture);
    WhitePawnSprite.setTextureRect(sf::IntRect(1571, 0, 314, 270));
    WhitePawnSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackPawnSprite;
    BlackPawnSprite.setTexture(pieceTexture);
    BlackPawnSprite.setTextureRect(sf::IntRect(1571, 335, 314, 270));
    BlackPawnSprite.setScale(0.34f, 0.34f);
    for (int col = 0; col < 8; ++col) {
        board[1][col].SetPiece(new Pawn(sf::Vector2i(1, col), 'B', BlackPawnSprite));
        board[6][col].SetPiece(new Pawn(sf::Vector2i(6, col), 'W', WhitePawnSprite));
    }
    // Initialize Rooks
    sf::Sprite WhiteRookSprite;
    WhiteRookSprite.setTexture(pieceTexture);
    WhiteRookSprite.setTextureRect(sf::IntRect(1270, 0, 314, 270));
    WhiteRookSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackRookSprite;
    BlackRookSprite.setTexture(pieceTexture);
    BlackRookSprite.setTextureRect(sf::IntRect(1270, 335, 314, 270));
    BlackRookSprite.setScale(0.34f, 0.34f);
    for (int i = 0; i < 8; i += 7) {
        board[0][i].SetPiece(new Rook(sf::Vector2i(0, i), 'B', BlackRookSprite));
        board[7][i].SetPiece(new Rook(sf::Vector2i(7, i), 'W', WhiteRookSprite));
    }
    // Initialize Knights
    sf::Sprite WhiteKnightSprite;
    WhiteKnightSprite.setTexture(pieceTexture);
    WhiteKnightSprite.setTextureRect(sf::IntRect(970, 0, 314, 270));
    WhiteKnightSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackKnightSprite;
    BlackKnightSprite.setTexture(pieceTexture);
    BlackKnightSprite.setTextureRect(sf::IntRect(970, 335, 314, 270));
    BlackKnightSprite.setScale(0.34f, 0.34f);
    for (int i = 1; i < 7; i += 5) {
        board[0][i].SetPiece(new Knight(sf::Vector2i(0, i), 'B', BlackKnightSprite));
        board[7][i].SetPiece(new Knight(sf::Vector2i(7, i), 'W', WhiteKnightSprite));
    }
    // Initialize Bishops
    sf::Sprite WhiteBishopSprite;
    WhiteBishopSprite.setTexture(pieceTexture);
    WhiteBishopSprite.setTextureRect(sf::IntRect(670, 0, 314, 270));
    WhiteBishopSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackBishopSprite;
    BlackBishopSprite.setTexture(pieceTexture);
    BlackBishopSprite.setTextureRect(sf::IntRect(670, 335, 314, 270));
    BlackBishopSprite.setScale(0.34f, 0.34f);
    for (int i = 2; i < 6; i += 3) {
        board[0][i].SetPiece(new Bishop(sf::Vector2i(0, i), 'B', BlackBishopSprite));
        board[7][i].SetPiece(new Bishop(sf::Vector2i(7, i), 'W', WhiteBishopSprite));
    }
    // Initialize Queens
    sf::Sprite WhiteQueenSprite;
    WhiteQueenSprite.setTexture(pieceTexture);
    WhiteQueenSprite.setTextureRect(sf::IntRect(320, 0, 340, 270));
    WhiteQueenSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackQueenSprite;
    BlackQueenSprite.setTexture(pieceTexture);
    BlackQueenSprite.setTextureRect(sf::IntRect(320, 335, 340, 270));
    BlackQueenSprite.setScale(0.34f, 0.34f);
    board[0][3].SetPiece(new Queen(sf::Vector2i(0, 3), 'B', BlackQueenSprite));
    board[7][3].SetPiece(new Queen(sf::Vector2i(7, 3), 'W', WhiteQueenSprite));
    // Initialize Kings
    sf::Sprite WhiteKingSprite;
    WhiteKingSprite.setTexture(pieceTexture);
    WhiteKingSprite.setTextureRect(sf::IntRect(0, 0, 314, 270));
    WhiteKingSprite.setScale(0.34f, 0.34f);

    sf::Sprite BlackKingSprite;
    BlackKingSprite.setTexture(pieceTexture);
    BlackKingSprite.setTextureRect(sf::IntRect(0, 335, 314, 270));
    BlackKingSprite.setScale(0.34f, 0.34f);
    board[0][4].SetPiece(new King(sf::Vector2i(0, 4), 'B', BlackKingSprite));
    board[7][4].SetPiece(new King(sf::Vector2i(7, 4), 'W', WhiteKingSprite));
}

sf::Vector2i Board::GetBoardPosition(const sf::Vector2i& mousePosition, int windowWidth) {
    int cellSize = windowWidth / 8;

    int col = mousePosition.x / cellSize;
    int row = mousePosition.y / cellSize;

    return sf::Vector2i(row, col);
}

// Graphical display
void Board::drawBoard(sf::RenderWindow& window) {
    int squareSize = 100;

    // Highlight last move positions
    if (lastFromPos.x != -1 && lastFromPos.y != -1) {
        sf::RectangleShape highlightFrom(sf::Vector2f(squareSize, squareSize));
        highlightFrom.setFillColor(sf::Color(105, 221, 237, 170));  // Light blue with 50% opacity
        highlightFrom.setPosition(lastFromPos.y * squareSize, lastFromPos.x * squareSize);
        window.draw(highlightFrom);
    }

    if (lastToPos.x != -1 && lastToPos.y != -1) {
        sf::RectangleShape highlightTo(sf::Vector2f(squareSize, squareSize));
        highlightTo.setFillColor(sf::Color(105, 221, 237, 170));  // Light blue with 50% opacity
        highlightTo.setPosition(lastToPos.y * squareSize, lastToPos.x * squareSize);
        window.draw(highlightTo);
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            if (piece != NULL) {
                piece->getSprite().setPosition((piece->getPosition().y * squareSize) + piece->getOffsetX(), (piece->getPosition().x * squareSize) + piece->getOffsetY());
                window.draw(piece->getSprite());
            }
        }
    }
}

// Debugging function
void Board::DisplayBoard(Board board) {
    const int boardSize = 8;
    const std::string columnDivider = " | ";
    const std::string rowDivider = " +-----+-----+-----+-----+-----+-----+-----+-----+";

    for (int row = 0; row < boardSize; row++) {
        std::cout << rowDivider << std::endl;
        for (int col = 0; col < boardSize; col++) {
            ChessPiece* piece = board.GetPiece(sf::Vector2i(row, col));
            std::cout << columnDivider;
            if (piece != nullptr) {
                std::cout << piece->getColor() << ":" << piece->getType();
            }
            else {
                std::cout << "   ";
            }
        }
        std::cout << columnDivider << std::endl;
    }
    std::cout << rowDivider << std::endl;
}