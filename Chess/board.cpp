#include "board.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"
#include <iostream>

Board::Board() : lastFromPos(-1, -1), lastToPos(-1, -1) {
    invalidMove.loadFromFile("assets/incorrect.wav");
    invalidMoveSound.setBuffer(invalidMove);
    invalidMoveSound.setVolume(100);

    promote.loadFromFile("assets/promote.wav");
    promoteSound.setBuffer(promote);
    promoteSound.setVolume(100);

    InitializePieces();
}

Board::~Board() {
}

bool Board::checkPromotionWhite(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted) {
    if (origPiece != nullptr &&
        (origPiece->getColor() == 'W' && whitesMove == true) &&
        origPiece->getType() == "P" && fromPos != toPos &&
        toPos.x == 0 &&
        origPiece->validateMove(toPos, board)) {

        lastFromPos = fromPos;
        lastToPos = toPos;
        drawBoard(window);
        window.display();

        // Load textures for queen, knight, rook, and bishop
        pieceTexture.loadFromFile("assets/chess_pieces.png");

        // Create sprites for each piece
        sf::Sprite WhiteQueenSprite;
        WhiteQueenSprite.setTexture(pieceTexture);
        WhiteQueenSprite.setTextureRect(sf::IntRect(320, 0, 340, 270));
        WhiteQueenSprite.setScale(0.34f, 0.34f);

        sf::Sprite WhiteRookSprite;
        WhiteRookSprite.setTexture(pieceTexture);
        WhiteRookSprite.setTextureRect(sf::IntRect(1270, 0, 314, 270));
        WhiteRookSprite.setScale(0.34f, 0.34f);

        sf::Sprite WhiteKnightSprite;
        WhiteKnightSprite.setTexture(pieceTexture);
        WhiteKnightSprite.setTextureRect(sf::IntRect(970, 0, 314, 270));
        WhiteKnightSprite.setScale(0.34f, 0.34f);

        sf::Sprite WhiteBishopSprite;
        WhiteBishopSprite.setTexture(pieceTexture);
        WhiteBishopSprite.setTextureRect(sf::IntRect(670, 0, 314, 270));
        WhiteBishopSprite.setScale(0.34f, 0.34f);

        // Position the sprites within the promotion window
        WhiteQueenSprite.setPosition(15, 20);
        WhiteRookSprite.setPosition(114, 20);
        WhiteKnightSprite.setPosition(130, 136);
        WhiteBishopSprite.setPosition(20, 136);

        // Create a new window for piece selection
        sf::RenderWindow promotionWindow(sf::VideoMode(245, 245), "Promote Pawn", sf::Style::None);
        promotionWindow.setPosition(sf::Vector2i((window.getPosition().x + window.getSize().x / 2) - 112,
            (window.getPosition().y + window.getSize().y / 2) - 78));

        makeWindowTransparent(promotionWindow, 210);

        // Disable the main window while the promotion window is active
        window.setActive(false);

        ChessPiece* selectedPiece = nullptr;
        while (selectedPiece == nullptr) {
            sf::Event event;
            while (promotionWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    // Prevent closing the window by any close event
                    promotionWindow.requestFocus(); // Bring the promotion window back to focus
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Get the global mouse position relative to the screen
                    sf::Vector2i globalMousePos = sf::Mouse::getPosition();

                    // Get the promotion window's global position and size
                    sf::Vector2i windowPos = promotionWindow.getPosition();
                    sf::Vector2u windowSize = promotionWindow.getSize();

                    // Check if the click is within the promotion window's bounds
                    if (globalMousePos.x >= windowPos.x && globalMousePos.x <= windowPos.x + static_cast<int>(windowSize.x) &&
                        globalMousePos.y >= windowPos.y && globalMousePos.y <= windowPos.y + static_cast<int>(windowSize.y)) {

                        // Calculate the position relative to the promotion window
                        sf::Vector2i mousePos = sf::Mouse::getPosition(promotionWindow);

                        if (mousePos.x < 123 && mousePos.y < 123) {
                            selectedPiece = new Queen(sf::Vector2i(toPos.x, toPos.y), 'W', WhiteQueenSprite);
                        }
                        else if (mousePos.x >= 123 && mousePos.y < 123) {
                            selectedPiece = new Rook(sf::Vector2i(toPos.x, toPos.y), 'W', WhiteRookSprite);
                        }
                        else if (mousePos.x >= 123 && mousePos.y >= 123) {
                            selectedPiece = new Knight(sf::Vector2i(toPos.x, toPos.y), 'W', WhiteKnightSprite);
                        }
                        else if (mousePos.x < 123 && mousePos.y >= 123) {
                            selectedPiece = new Bishop(sf::Vector2i(toPos.x, toPos.y), 'W', WhiteBishopSprite);
                        }
                    }
                }
            }

            // Ensure the promotion window remains on top and active
            promotionWindow.requestFocus();  // Request focus if the main window was clicked

            // Clear and draw the promotion window
            promotionWindow.clear(sf::Color::White);
            promotionWindow.draw(WhiteQueenSprite);
            promotionWindow.draw(WhiteRookSprite);
            promotionWindow.draw(WhiteKnightSprite);
            promotionWindow.draw(WhiteBishopSprite);
            promotionWindow.display();
        }

        // Close the promotion window
        promotionWindow.close();

        // Re-enable the main window after promotion is done
        window.setActive(true);
        window.requestFocus();  // Ensure the main window gets focus back

        // Promote the pawn to the selected piece
        if (selectedPiece != nullptr) {
            board[fromPos.x][fromPos.y].Clear();
            board[toPos.x][toPos.y].SetPiece(selectedPiece);
            whitesMove = !whitesMove;
            moveCompleted = true;
        }

        // Close the promotion window after a piece is selected
        return (moveCompleted);
    }
}

bool Board::checkPromotionBlack(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted) {
    if (origPiece != nullptr &&
        (origPiece->getColor() == 'B' && !whitesMove) &&
        origPiece->getType() == "P" && fromPos != toPos &&
        toPos.x == 7 &&
        origPiece->validateMove(toPos, board)) {

        lastFromPos = fromPos;
        lastToPos = toPos;
        drawBoard(window);
        window.display();

        // Load textures for queen, knight, rook, and bishop
        pieceTexture.loadFromFile("assets/chess_pieces.png");

        // Create sprites for each piece
        sf::Sprite BlackQueenSprite;
        BlackQueenSprite.setTexture(pieceTexture);
        BlackQueenSprite.setTextureRect(sf::IntRect(320, 335, 340, 270));
        BlackQueenSprite.setScale(0.34f, 0.34f);

        sf::Sprite BlackRookSprite;
        BlackRookSprite.setTexture(pieceTexture);
        BlackRookSprite.setTextureRect(sf::IntRect(1270, 335, 314, 270));
        BlackRookSprite.setScale(0.34f, 0.34f);

        sf::Sprite BlackKnightSprite;
        BlackKnightSprite.setTexture(pieceTexture);
        BlackKnightSprite.setTextureRect(sf::IntRect(970, 335, 314, 270));
        BlackKnightSprite.setScale(0.34f, 0.34f);

        sf::Sprite BlackBishopSprite;
        BlackBishopSprite.setTexture(pieceTexture);
        BlackBishopSprite.setTextureRect(sf::IntRect(670, 335, 314, 270));
        BlackBishopSprite.setScale(0.34f, 0.34f);

        // Position the sprites within the promotion window
        BlackQueenSprite.setPosition(15, 20);
        BlackRookSprite.setPosition(114, 20);
        BlackKnightSprite.setPosition(130, 136);
        BlackBishopSprite.setPosition(20, 136);

        // Create a new window for piece selection
        sf::RenderWindow promotionWindow(sf::VideoMode(245, 245), "Promote Pawn", sf::Style::None);
        promotionWindow.setPosition(sf::Vector2i((window.getPosition().x + window.getSize().x / 2) - 112,
            (window.getPosition().y + window.getSize().y / 2) - 78));

        makeWindowTransparent(promotionWindow, 210);

        // Disable the main window while the promotion window is active
        window.setActive(false);

        ChessPiece* selectedPiece = nullptr;
        while (selectedPiece == nullptr) {
            sf::Event event;
            while (promotionWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    // Prevent closing the window by any close event
                    promotionWindow.requestFocus(); // Bring the promotion window back to focus
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Get the global mouse position relative to the screen
                    sf::Vector2i globalMousePos = sf::Mouse::getPosition();

                    // Get the promotion window's global position and size
                    sf::Vector2i windowPos = promotionWindow.getPosition();
                    sf::Vector2u windowSize = promotionWindow.getSize();

                    // Check if the click is within the promotion window's bounds
                    if (globalMousePos.x >= windowPos.x && globalMousePos.x <= windowPos.x + static_cast<int>(windowSize.x) &&
                        globalMousePos.y >= windowPos.y && globalMousePos.y <= windowPos.y + static_cast<int>(windowSize.y)) {

                        // Calculate the position relative to the promotion window
                        sf::Vector2i mousePos = sf::Mouse::getPosition(promotionWindow);

                        if (mousePos.x < 123 && mousePos.y < 123) {
                            selectedPiece = new Queen(sf::Vector2i(toPos.x, toPos.y), 'B', BlackQueenSprite);
                        }
                        else if (mousePos.x >= 123 && mousePos.y < 123) {
                            selectedPiece = new Rook(sf::Vector2i(toPos.x, toPos.y), 'B', BlackRookSprite);
                        }
                        else if (mousePos.x >= 123 && mousePos.y >= 123) {
                            selectedPiece = new Knight(sf::Vector2i(toPos.x, toPos.y), 'B', BlackKnightSprite);
                        }
                        else if (mousePos.x < 123 && mousePos.y >= 123) {
                            selectedPiece = new Bishop(sf::Vector2i(toPos.x, toPos.y), 'B', BlackBishopSprite);
                        }
                    }
                }
            }

            // Ensure the promotion window remains on top and active
            promotionWindow.requestFocus();  // Request focus if the main window was clicked

            // Clear and draw the promotion window
            promotionWindow.clear(sf::Color::White);
            promotionWindow.draw(BlackQueenSprite);
            promotionWindow.draw(BlackRookSprite);
            promotionWindow.draw(BlackKnightSprite);
            promotionWindow.draw(BlackBishopSprite);
            promotionWindow.display();
        }

        // Close the promotion window
        promotionWindow.close();

        // Re-enable the main window after promotion is done
        window.setActive(true);
        window.requestFocus();  // Ensure the main window gets focus back

        // Promote the pawn to the selected piece
        if (selectedPiece != nullptr) {
            board[fromPos.x][fromPos.y].Clear();
            board[toPos.x][toPos.y].SetPiece(selectedPiece);
            whitesMove = !whitesMove;
            moveCompleted = true;
        }

        // Close the promotion window after a piece is selected
        return (moveCompleted);
    }
}

void Board::makeWindowTransparent(sf::RenderWindow& window, BYTE transparency) {
    HWND hwnd = window.getSystemHandle();
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, transparency, LWA_ALPHA);
}


bool Board::checkCastle(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& toPos, sf::Vector2i& fromPos, sf::Vector2i& lastToPos, sf::Vector2i& lastFromPos) {
    // White castling
    if (origPiece->getColor() == 'W' && origPiece->getType() == "K" && whitesMove && !origPiece->getHasMoved()) {
        // King-side castling
        if (board[7][7].GetPiece() != NULL && board[7][7].GetPiece()->getType() == "R" &&
            board[7][7].GetPiece()->getColor() == 'W' && !board[7][7].GetPiece()->getHasMoved() &&
            board[7][6].GetPiece() == NULL && board[7][5].GetPiece() == NULL &&
            toPos.x == 7 && (toPos.y == 6 || toPos.y == 7)) {
            
            origPiece->validateMove(toPos, board);
            whitesMove = !whitesMove;
            lastFromPos = fromPos;
            lastToPos = sf::Vector2i(7, 7);
            return (true);
        }
        // Queen-side castling
        if (board[7][0].GetPiece() != NULL && board[7][0].GetPiece()->getType() == "R" &&
            board[7][0].GetPiece()->getColor() == 'W' && !board[7][0].GetPiece()->getHasMoved() &&
            board[7][1].GetPiece() == NULL && board[7][2].GetPiece() == NULL && board[7][3].GetPiece() == NULL &&
            toPos.x == 7 && (toPos.y == 2 || toPos.y == 1 || toPos.y == 0)) {

            origPiece->validateMove(toPos, board);
            whitesMove = !whitesMove;
            lastFromPos = fromPos;
            lastToPos = sf::Vector2i(7, 0);
            return (true);
        }
    }

    // Black castling
    if (origPiece->getColor() == 'B' && origPiece->getType() == "K" && !whitesMove && !origPiece->getHasMoved()) {
        // King-side castling
        if (board[0][7].GetPiece() != NULL && board[0][7].GetPiece()->getType() == "R" &&
            board[0][7].GetPiece()->getColor() == 'B' && !board[0][7].GetPiece()->getHasMoved() &&
            board[0][6].GetPiece() == NULL && board[0][5].GetPiece() == NULL &&
            toPos.x == 0 && (toPos.y == 6 || toPos.y == 7)) {

            origPiece->validateMove(toPos, board);
            whitesMove = !whitesMove;
            lastFromPos = fromPos;
            lastToPos = sf::Vector2i(0, 7);
            return (true);
        }
        // Queen-side castling
        if (board[0][0].GetPiece() != NULL && board[0][0].GetPiece()->getType() == "R" &&
            board[0][0].GetPiece()->getColor() == 'B' && !board[0][0].GetPiece()->getHasMoved() &&
            board[0][1].GetPiece() == NULL && board[0][2].GetPiece() == NULL && board[0][3].GetPiece() == NULL &&
            toPos.x == 0 && (toPos.y == 2 || toPos.y == 1 || toPos.y == 0)) {

            origPiece->validateMove(toPos, board);
            whitesMove = !whitesMove;
            lastFromPos = fromPos;
            lastToPos = sf::Vector2i(0, 0);
            return (true);
        }
    }
    return (false);
}

void Board::updateLastMovedPiece(ChessPiece* origPiece) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            if (piece != nullptr) {
                if (piece->getLastMoved() == true) {
                    piece->setLastMoved(false);
                }
            }
        }
    }
    origPiece->setLastMoved(true);
}

bool Board::MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove, sf::RenderWindow& window) {
    bool moveCompleted = false;

    ChessPiece* origPiece = board[fromPos.x][fromPos.y].GetPiece();
    ChessPiece* destPiece = board[toPos.x][toPos.y].GetPiece();

    // Check for castling
    if (checkCastle(origPiece, whitesMove, toPos, fromPos, lastToPos, lastFromPos)) return (true);

    if (checkPromotionWhite(origPiece, whitesMove, fromPos, toPos, window, moveCompleted) || checkPromotionBlack(origPiece, whitesMove, fromPos, toPos, window, moveCompleted)) {
        promoteSound.play();
        return (true);
    }

    if (origPiece != nullptr &&
        ((origPiece->getColor() == 'W' && whitesMove == true) || (origPiece->getColor() == 'B' && whitesMove == false)) &&
        fromPos != toPos && origPiece->validateMove(toPos, board)) {

        if (destPiece != nullptr && destPiece->getColor() != origPiece->getColor()) {
            board[toPos.x][toPos.y].Clear();
        }
        else if (destPiece != nullptr && destPiece->getColor() == origPiece->getColor()) {
            invalidMoveSound.play();
            return (moveCompleted);
        }

        origPiece->setPosition(toPos);
        board[toPos.x][toPos.y].SetPiece(origPiece);
        board[fromPos.x][fromPos.y].Clear();
        
        updateLastMovedPiece(origPiece);

        lastFromPos = fromPos;
        lastToPos = toPos;

        moveCompleted = true;
        whitesMove = !whitesMove;
    }

    if (!moveCompleted) {
        invalidMoveSound.play();
        fromPos = sf::Vector2i(-1, -1);
    }

    return (moveCompleted);
}

ChessPiece* Board::GetPiece(sf::Vector2i piecePos) {
    return board[piecePos.x][piecePos.y].GetPiece();
}

void Board::InitializePieces() {
    // Load texture
    pieceTexture.loadFromFile("assets/chess_pieces.png");
    
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