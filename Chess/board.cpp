#include "board.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"
#include <iostream>

// CONSTRUCTOR
// PRE: 
// POST: Board object created and all pieces are initilized on their starting squares.
Board::Board() : lastFromPos(-1, -1), lastToPos(-1, -1), fiftyMoveCounter(0) {
    invalidMove.loadFromFile("assets/incorrect.wav");
    invalidMoveSound.setBuffer(invalidMove);
    invalidMoveSound.setVolume(100);

    promote.loadFromFile("assets/promote.wav");
    promoteSound.setBuffer(promote);
    promoteSound.setVolume(100);

    moveWhite.loadFromFile("assets/move-self.wav");
    moveWhiteSound.setBuffer(moveWhite);
    moveWhiteSound.setVolume(100);

    moveBlack.loadFromFile("assets/move-opponent.wav");
    moveBlackSound.setBuffer(moveBlack);
    moveBlackSound.setVolume(100);

    capture.loadFromFile("assets/capture.wav");
    captureSound.setBuffer(capture);
    captureSound.setVolume(100);

    castle.loadFromFile("assets/castle.wav");
    castleSound.setBuffer(castle);
    castleSound.setVolume(100);

    check.loadFromFile("assets/move-check.wav");
    checkSound.setBuffer(check);
    checkSound.setVolume(100);

    china.loadFromFile("assets/China.wav");
    chinaSound.setBuffer(china);
    chinaSound.setVolume(100);

    gameEnd.loadFromFile("assets/game-end.wav");
    gameEndSound.setBuffer(gameEnd);
    gameEndSound.setVolume(100);

    bell.loadFromFile("assets/bell.wav");
    bellSound.setBuffer(bell);
    bellSound.setVolume(100);

    InitializePieces();
}

// DESTRUCTOR
// PRE: 
// POST:
Board::~Board() {

}

// PRE: 
// POST: All Pieces on board are deleted and re-initilized along with
//       lastFromPos and lastToPos being reset to (-1, -1).
void Board::resetBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessPiece* piece = board[row][col].GetPiece();
            if (piece != nullptr) {
                delete piece;
                board[row][col].SetPiece(nullptr);
            }
        }
    }
    positionCounts.clear();
    fiftyMoveCounter = 0;
    InitializePieces();
    lastFromPos = sf::Vector2i(-1, -1);
    lastToPos = sf::Vector2i(-1, -1);
}

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
bool Board::checkPromotionWhite(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState) {
    if (origPiece != nullptr &&
        (origPiece->getColor() == 'W' && whitesMove == true) &&
        origPiece->getType() == "P" && fromPos != toPos &&
        toPos.x == 0 &&
        origPiece->validateMove(toPos, board, legalMoves)) {

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
            if (selectedPiece->getType() == "R") {
                selectedPiece->setHasMoved(true);
            }
            board[fromPos.x][fromPos.y].Clear();
            board[toPos.x][toPos.y].SetPiece(selectedPiece);
            if (!checkForDrawByInsufficientMaterial(gameState) && !checkForCheckmateOrCheck(whitesMove, gameState, false) && !checkForStalemate(whitesMove, gameState, false)) promoteSound.play();
            updatePositionCounts();
            fiftyMoveCounter = 0;
            whitesMove = !whitesMove;
            moveCompleted = true;
        }
        updateLastMovedPiece(selectedPiece);
        // Close the promotion window after a piece is selected
    }
    return (moveCompleted);
}

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
bool Board::checkPromotionBlack(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, sf::RenderWindow& window, bool moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState) {
    if (origPiece != nullptr &&
        (origPiece->getColor() == 'B' && !whitesMove) &&
        origPiece->getType() == "P" && fromPos != toPos &&
        toPos.x == 7 &&
        origPiece->validateMove(toPos, board, legalMoves)) {
        
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
            if (selectedPiece->getType() == "R") {
                selectedPiece->setHasMoved(true);
            }
            board[fromPos.x][fromPos.y].Clear();
            board[toPos.x][toPos.y].SetPiece(selectedPiece);
            if (!checkForDrawByInsufficientMaterial(gameState) && !checkForCheckmateOrCheck(whitesMove, gameState, false) && !checkForStalemate(whitesMove, gameState, false)) promoteSound.play();
            updatePositionCounts();
            fiftyMoveCounter = 0;
            whitesMove = !whitesMove;
            moveCompleted = true;
        }

        updateLastMovedPiece(selectedPiece);
        // Close the promotion window after a piece is selected
    }
    return (moveCompleted);
}

// PRE: origPiece is a ChessPiece object that could be null, 
//      whitesMove is a bool that represents whos turn it is, 
//      fromPos is a sf::Vector2i representing where the piece is moving from,
//      toPos is a sf::Vector2i representing where the piece is moving to,
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      gameState is an int representing the current state of the game
// POST: White king is either castled king-side or queen side or
//       Black king is either castled king-side or queen side,
//       or move is invalid.
bool Board::checkCastle(ChessPiece* origPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int &gameState) {
    // White castling
    if (origPiece->getColor() == 'W' && origPiece->getType() == "K" && whitesMove && !origPiece->getHasMoved()) {
        // King-side castling
        if (board[7][7].GetPiece() != nullptr && board[7][7].GetPiece()->getType() == "R" &&
            board[7][7].GetPiece()->getColor() == 'W' && !board[7][7].GetPiece()->getHasMoved() &&
            board[7][6].GetPiece() == nullptr && board[7][5].GetPiece() == nullptr &&
            toPos.x == 7 && (toPos.y == 6 || toPos.y == 7)) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            board[7][4].Clear();
            board[7][5].SetPiece(origPiece);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[7][5].Clear();
                board[7][6].SetPiece(origPiece);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[7][6].Clear();
                    board[7][4].SetPiece(origPiece);
                    ChessPiece* rook = board[7][7].GetPiece();

                    board[7][5].SetPiece(rook);
                    board[7][7].Clear();
                    board[7][6].SetPiece(origPiece);
                    board[7][4].Clear();

                    rook->setHasMoved(true);
                    origPiece->setHasMoved(true);
                    rook->setPosition(sf::Vector2i(7, 5));
                    origPiece->setPosition(sf::Vector2i(7, 6));

                    whitesMove = !whitesMove;
                    lastFromPos = fromPos;
                    lastToPos = sf::Vector2i(7, 7);
                    if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) castleSound.play();
                    updateLastMovedPiece(origPiece);
                    updatePositionCounts();
                    fiftyMoveCounter++;
                    return (true);
                }
            }
            if (!passedFirstCheck) {
                board[7][5].Clear();
                board[7][4].SetPiece(origPiece);
            }
            if (!passedSecondCheck) {
                board[7][6].Clear();
                board[7][4].SetPiece(origPiece);
            }
            return (false);
        }
        // Queen-side castling
        if (board[7][0].GetPiece() != nullptr && board[7][0].GetPiece()->getType() == "R" &&
            board[7][0].GetPiece()->getColor() == 'W' && !board[7][0].GetPiece()->getHasMoved() &&
            board[7][1].GetPiece() == nullptr && board[7][2].GetPiece() == nullptr && board[7][3].GetPiece() == nullptr &&
            toPos.x == 7 && (toPos.y == 2 || toPos.y == 1 || toPos.y == 0)) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            bool passedThirdCheck = false;
            board[7][4].Clear();
            board[7][3].SetPiece(origPiece);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[7][3].Clear();
                board[7][2].SetPiece(origPiece);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[7][2].Clear();
                    board[7][1].SetPiece(origPiece);
                    if (!isKingInCheck(!whitesMove, board)) {
                        passedThirdCheck = true;
                        board[7][1].Clear();
                        board[7][4].SetPiece(origPiece);
                        ChessPiece* rook = board[7][0].GetPiece();

                        board[7][3].SetPiece(rook);
                        board[7][0].Clear();
                        board[7][2].SetPiece(origPiece);
                        board[7][4].Clear();

                        rook->setHasMoved(true);
                        origPiece->setHasMoved(true);
                        rook->setPosition(sf::Vector2i(7, 3));
                        origPiece->setPosition(sf::Vector2i(7, 2));

                        whitesMove = !whitesMove;
                        lastFromPos = fromPos;
                        lastToPos = sf::Vector2i(7, 0);
                        if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) castleSound.play();
                        updateLastMovedPiece(origPiece);
                        updatePositionCounts();
                        fiftyMoveCounter++;
                        return (true);
                    }
                }
            }
            if (!passedFirstCheck) {
                board[7][3].Clear();
                board[7][4].SetPiece(origPiece);
            }
            if (!passedSecondCheck) {
                board[7][2].Clear();
                board[7][4].SetPiece(origPiece);
            }
            if (!passedThirdCheck) {
                board[7][1].Clear();
                board[7][4].SetPiece(origPiece);
            }
            return (false);
        }
    }

    // Black castling
    if (origPiece->getColor() == 'B' && origPiece->getType() == "K" && !whitesMove && !origPiece->getHasMoved()) {
        // King-side castling
        if (board[0][7].GetPiece() != nullptr && board[0][7].GetPiece()->getType() == "R" &&
            board[0][7].GetPiece()->getColor() == 'B' && !board[0][7].GetPiece()->getHasMoved() &&
            board[0][6].GetPiece() == nullptr && board[0][5].GetPiece() == nullptr &&
            toPos.x == 0 && (toPos.y == 6 || toPos.y == 7)) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            board[0][4].Clear();
            board[0][5].SetPiece(origPiece);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[0][5].Clear();
                board[0][6].SetPiece(origPiece);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[0][6].Clear();
                    board[0][4].SetPiece(origPiece);
                    ChessPiece* rook = board[0][7].GetPiece();

                    board[0][5].SetPiece(rook);
                    board[0][7].Clear();
                    board[0][6].SetPiece(origPiece);
                    board[0][4].Clear();

                    rook->setHasMoved(true);
                    origPiece->setHasMoved(true);
                    rook->setPosition(sf::Vector2i(0, 5));
                    origPiece->setPosition(sf::Vector2i(0, 6));

                    whitesMove = !whitesMove;
                    lastFromPos = fromPos;
                    lastToPos = sf::Vector2i(0, 7);
                    if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) castleSound.play();
                    updateLastMovedPiece(origPiece);
                    updatePositionCounts();
                    fiftyMoveCounter++;
                    return (true);
                }
            }
            if (!passedFirstCheck) {
                board[0][5].Clear();
                board[0][4].SetPiece(origPiece);
            }
            if (!passedSecondCheck) {
                board[0][6].Clear();
                board[0][4].SetPiece(origPiece);
            }
            return (false);
        }
        // Queen-side castling
        if (board[0][0].GetPiece() != nullptr && board[0][0].GetPiece()->getType() == "R" &&
            board[0][0].GetPiece()->getColor() == 'B' && !board[0][0].GetPiece()->getHasMoved() &&
            board[0][1].GetPiece() == nullptr && board[0][2].GetPiece() == nullptr && board[0][3].GetPiece() == nullptr &&
            toPos.x == 0 && (toPos.y == 2 || toPos.y == 1 || toPos.y == 0)) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            bool passedThirdCheck = false;
            board[0][4].Clear();
            board[0][3].SetPiece(origPiece);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[0][3].Clear();
                board[0][2].SetPiece(origPiece);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[0][2].Clear();
                    board[0][1].SetPiece(origPiece);
                    if (!isKingInCheck(!whitesMove, board)) {
                        passedThirdCheck = true;
                        board[0][1].Clear();
                        board[0][4].SetPiece(origPiece);
                        ChessPiece* rook = board[0][0].GetPiece();

                        board[0][3].SetPiece(rook);
                        board[0][0].Clear();
                        board[0][2].SetPiece(origPiece);
                        board[0][4].Clear();

                        rook->setHasMoved(true);
                        origPiece->setHasMoved(true);
                        rook->setPosition(sf::Vector2i(0, 3));
                        origPiece->setPosition(sf::Vector2i(0, 2));

                        whitesMove = !whitesMove;
                        lastFromPos = fromPos;
                        lastToPos = sf::Vector2i(0, 0);
                        if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) castleSound.play();
                        updateLastMovedPiece(origPiece);
                        updatePositionCounts();
                        fiftyMoveCounter++;
                        return (true);
                    }
                }
            }
            if (!passedFirstCheck) {
                board[0][3].Clear();
                board[0][4].SetPiece(origPiece);
            }
            if (!passedSecondCheck) {
                board[0][2].Clear();
                board[0][4].SetPiece(origPiece);
            }
            if (!passedThirdCheck) {
                board[0][1].Clear();
                board[0][4].SetPiece(origPiece);
            }
            return (false);
        }
    }
    return (false);
}

// PRE: origPiece is a ChessPiece object that could be null,
//      destPiece is a ChessPiece object that could be null, 
//      whitesMove is a bool that represents whos turn it is, 
//      fromPos is a sf::Vector2i representing where the piece is moving from,
//      toPos is a sf::Vector2i representing where the piece is moving to,
//      gameState is an int representing the current state of the game
// POST: White pawn captures en passant or Black pawn captures en passant
//       or move is invalid.
bool Board::checkEnPassant(ChessPiece* origPiece, ChessPiece* destPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, int& gameState) {
    if (destPiece == nullptr &&
        (origPiece->getColor() == 'W' &&
            toPos.x == origPiece->getPosition().x - 1 &&
            board[toPos.x + 1][toPos.y].GetPiece() != nullptr &&
            board[toPos.x + 1][toPos.y].GetPiece()->getType() == "P" &&
            board[toPos.x + 1][toPos.y].GetPiece()->getColor() != origPiece->getColor() &&
            board[toPos.x + 1][toPos.y].GetPiece()->getLastMoved() == true &&
            board[toPos.x + 1][toPos.y].GetPiece()->getJustDoubleJumped() &&
            board[toPos.x + 1][toPos.y].GetPiece()->getSquaresMoved() == 2) ||
        (origPiece->getColor() == 'B' &&
            toPos.x == origPiece->getPosition().x + 1 &&
            board[toPos.x - 1][toPos.y].GetPiece() != nullptr &&
            board[toPos.x - 1][toPos.y].GetPiece()->getType() == "P" &&
            board[toPos.x - 1][toPos.y].GetPiece()->getColor() != origPiece->getColor() &&
            board[toPos.x - 1][toPos.y].GetPiece()->getLastMoved() == true &&
            board[toPos.x - 1][toPos.y].GetPiece()->getJustDoubleJumped() &&
            board[toPos.x - 1][toPos.y].GetPiece()->getSquaresMoved() == 2)) {

        if (origPiece->getColor() == 'W') {
            ChessPiece* otherPawn = board[toPos.x + 1][toPos.y].GetPiece();
            board[toPos.x + 1][toPos.y].Clear();
            board[origPiece->getPosition().x][origPiece->getPosition().y].Clear();
            board[toPos.x][toPos.y].SetPiece(origPiece);
            if (isKingInCheck(!whitesMove, board)) {
                board[toPos.x + 1][toPos.y].SetPiece(otherPawn);
                board[origPiece->getPosition().x][origPiece->getPosition().y].SetPiece(origPiece);
                board[toPos.x][toPos.y].Clear();
                return (false);
            }
        }

        if (origPiece->getColor() == 'B') {
            ChessPiece* otherPawn = board[toPos.x - 1][toPos.y].GetPiece();
            board[toPos.x - 1][toPos.y].Clear();
            board[origPiece->getPosition().x][origPiece->getPosition().y].Clear();
            board[toPos.x][toPos.y].SetPiece(origPiece);
            if (isKingInCheck(!whitesMove, board)) {
                board[toPos.x - 1][toPos.y].SetPiece(otherPawn);
                board[origPiece->getPosition().x][origPiece->getPosition().y].SetPiece(origPiece);
                board[toPos.x][toPos.y].Clear();
                return (false);
            }
        }

        origPiece->setPosition(toPos);
        origPiece->setLastMoved(true);

        lastFromPos = fromPos;
        lastToPos = toPos;
        whitesMove = !whitesMove;
        
        if (!checkForCheckmateOrCheck(whitesMove, gameState, false) && !checkForStalemate(whitesMove, gameState, false)) captureSound.play();
        
        updatePositionCounts();
        fiftyMoveCounter = 0;

        return (true);
    }
}

// PRE: origPiece is a ChessPiece object that could be null,
//      destPiece is a ChessPiece object that could be null,
//      whitesMove is a bool that represents whos turn it is, 
//      fromPos is a sf::Vector2i representing where the piece is moving from,
//      toPos is a sf::Vector2i representing where the piece is moving to,
//      moveCompleted is a bool that determines whether the move was valid or not,
//      legalMoves is a hashmap of all the legal moves of whoever's turn it is,
//      gameState is an int representing the current state of the game
// POST: Move is completed or move is invalid.
bool Board::checkNormalMove(ChessPiece* origPiece, ChessPiece* destPiece, bool& whitesMove, sf::Vector2i& fromPos, sf::Vector2i& toPos, bool& moveCompleted, std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves, int& gameState) {
    bool playCaptureSound = false;

    if (origPiece != nullptr &&
        ((origPiece->getColor() == 'W' && whitesMove) || (origPiece->getColor() == 'B' && !whitesMove)) &&
        fromPos != toPos && origPiece->validateMove(toPos, board, legalMoves)) {
        
        if (destPiece != nullptr && destPiece->getColor() != origPiece->getColor()) {
            board[toPos.x][toPos.y].Clear();
            playCaptureSound = true;
        }
        else if (destPiece != nullptr && destPiece->getColor() == origPiece->getColor()) {
            invalidMoveSound.play();
            return (moveCompleted);
        }

        origPiece->setPosition(toPos);
        board[toPos.x][toPos.y].SetPiece(origPiece);
        board[fromPos.x][fromPos.y].Clear();

        updateLastMovedPiece(origPiece);

        updatePositionCounts();

        if (!checkForCheckmateOrCheck(whitesMove, gameState, false)) {
            if (!checkForStalemate(whitesMove, gameState, false)) {
                if (playCaptureSound) {
                    fiftyMoveCounter = 0;
                    if (destPiece->getType() != "Q") {
                        captureSound.play();
                    } else {
                        bellSound.play();
                    }
                }
                else {
                    if (origPiece->getType() == "P") {
                        fiftyMoveCounter = 0;
                    }
                    else {
                        fiftyMoveCounter++;
                    }
                    if (origPiece->getColor() == 'W') moveWhiteSound.play();
                    if (origPiece->getColor() == 'B') moveBlackSound.play();
                }
                checkForDrawByInsufficientMaterial(gameState);
                checkForDrawByRepetition(gameState);
                checkForDrawByFiftyMoveRule(gameState);
            }
        }

        lastFromPos = fromPos;
        lastToPos = toPos;

        moveCompleted = true;
        whitesMove = !whitesMove;

    }
    return (moveCompleted);
}

// PRE: fromPos is a sf::Vector2i representing where the piece is moving from,
//      toPos is a sf::Vector2i representing where the piece is moving to,
//      whitesMove is a bool that represents whos turn it is, 
//      window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//      moveCompleted is a bool that determines whether the move was valid or not,
//      gameState is an int representing the current state of the game
// POST: Determines if move is special (castling, en passant, pawn promotion) or normal and whether
//       or not the move is valid.
bool Board::MovePiece(sf::Vector2i& fromPos, sf::Vector2i toPos, bool& whitesMove, sf::RenderWindow& window, int& gameState) {

    std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves = getLegalMoves(whitesMove);
    /*for (const auto& [pieceType, moves] : legalMoves) {
        std::cout << "Piece Type: " << pieceType << std::endl;
        if (moves.empty()) {
            std::cout << "  No legal moves." << std::endl;
        }
        else {
            for (const auto& move : moves) {
                std::cout << "  Move to: (" << move.x << ", " << move.y << ")" << std::endl;
            }
        }
    }

    std::cout << fiftyMoveCounter << std::endl;*/

    bool moveCompleted = false;

    ChessPiece* origPiece = board[fromPos.x][fromPos.y].GetPiece();
    ChessPiece* destPiece = board[toPos.x][toPos.y].GetPiece();

    // Check for castling
    if (checkCastle(origPiece, whitesMove, fromPos, toPos, legalMoves, gameState)) return (true);

    // Check for pawn promotion
    if (checkPromotionWhite(origPiece, whitesMove, fromPos, toPos, window, moveCompleted, legalMoves, gameState) ||
        checkPromotionBlack(origPiece, whitesMove, fromPos, toPos, window, moveCompleted, legalMoves, gameState)) return (true);

    // Check for en passant
    if (checkEnPassant(origPiece, destPiece, whitesMove, fromPos, toPos, gameState)) return (true);

    // Check for any other move
    moveCompleted = checkNormalMove(origPiece, destPiece, whitesMove, fromPos, toPos, moveCompleted, legalMoves, gameState);

    if (!moveCompleted) {
        invalidMoveSound.play();
        fromPos = sf::Vector2i(-1, -1);
        toPos = sf::Vector2i(-1, -1);
    }

    return (moveCompleted);
}

// PRE: whitesMove is a bool that represents whos turn it is,
//      board is a reference to the internal state of the Board object
// POST: determines whether or not the opposite color king is in check
//       based on whos turn it is.
bool Board::isKingInCheck(bool whitesMove, Square (&board)[8][8]) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            // After black makes a valid move check if white king is in check
            if (piece != nullptr && piece->getColor() == 'B' && !whitesMove) {
                if (piece->canPieceSeeTheKing(board)) return (true);
            }
            // After white makes a valid move check if black king is in check
            if (piece != nullptr && piece->getColor() == 'W' && whitesMove) {
                if (piece->canPieceSeeTheKing(board)) return (true);
            }
        }
    }
    return (false);
}

// PRE: whitesMove is a bool that represents whos turn it is,
// POST: RV is a hashmap of all legal moves from whoever's turn it is,
//       keys = piece type, values = vectors of sf::Vector2i's representing valid positions
//       to move to.
std::unordered_map<std::string, std::vector<sf::Vector2i>> Board::getLegalMoves(bool whitesMove) {
    std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            // Get all legal moves with the black pieces
            if (piece != nullptr && piece->getColor() == 'B' && !whitesMove) {
                piece->allLegalMoves(legalMoves, board, whitesMove);
            }
            // Get all legal moves with the white pieces
            if (piece != nullptr && piece->getColor() == 'W' && whitesMove) {
                piece->allLegalMoves(legalMoves, board, whitesMove);
            }
        }
    }
    return (legalMoves);
}

// PRE:
// POST:
void Board::addCastlingToLegalMoves(std::unordered_map<std::string, std::vector<sf::Vector2i>>& legalMoves, bool whitesMove, int gameState) {
    ChessPiece* whiteKing = board[7][4].GetPiece();
    if (whiteKing != nullptr && whiteKing->getColor() == 'W' && whiteKing->getType() == "K" && whitesMove && !whiteKing->getHasMoved()) {
        // King-side castling
        if (board[7][7].GetPiece() != nullptr && board[7][7].GetPiece()->getType() == "R" &&
            board[7][7].GetPiece()->getColor() == 'W' && !board[7][7].GetPiece()->getHasMoved() &&
            board[7][6].GetPiece() == nullptr && board[7][5].GetPiece() == nullptr) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            board[7][4].Clear();
            board[7][5].SetPiece(whiteKing);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[7][5].Clear();
                board[7][6].SetPiece(whiteKing);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[7][6].Clear();
                    board[7][4].SetPiece(whiteKing);
                    ChessPiece* rook = board[7][7].GetPiece();

                    board[7][5].SetPiece(rook);
                    board[7][7].Clear();
                    board[7][6].SetPiece(whiteKing);
                    board[7][4].Clear();

                    rook->setPosition(sf::Vector2i(7, 5));
                    whiteKing->setPosition(sf::Vector2i(7, 6));

                    if (!checkForCheckmateOrCheck(!whitesMove, gameState, true) && !checkForStalemate(!whitesMove, gameState, true)) {
                        std::string posKey = whiteKing->getType() + std::to_string(whiteKing->getPosition().x) + std::to_string(whiteKing->getPosition().y);
                        legalMoves[posKey].push_back(sf::Vector2i(7, 6));
                        legalMoves[posKey].push_back(sf::Vector2i(7, 7));
                    }

                    board[7][5].Clear();
                    board[7][7].SetPiece(rook);
                    board[7][6].Clear();
                    board[7][4].SetPiece(whiteKing);

                    rook->setPosition(sf::Vector2i(7, 7));
                    whiteKing->setPosition(sf::Vector2i(7, 4));
                }
            }
            if (!passedFirstCheck) {
                board[7][5].Clear();
                board[7][4].SetPiece(whiteKing);
            }
            if (!passedSecondCheck) {
                board[7][6].Clear();
                board[7][4].SetPiece(whiteKing);
            }
        }
        if (board[7][0].GetPiece() != nullptr && board[7][0].GetPiece()->getType() == "R" &&
            board[7][0].GetPiece()->getColor() == 'W' && !board[7][0].GetPiece()->getHasMoved() &&
            board[7][1].GetPiece() == nullptr && board[7][2].GetPiece() == nullptr && board[7][3].GetPiece() == nullptr) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            bool passedThirdCheck = false;
            board[7][4].Clear();
            board[7][3].SetPiece(whiteKing);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[7][3].Clear();
                board[7][2].SetPiece(whiteKing);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[7][2].Clear();
                    board[7][1].SetPiece(whiteKing);
                    if (!isKingInCheck(!whitesMove, board)) {
                        passedThirdCheck = true;
                        board[7][1].Clear();
                        board[7][4].SetPiece(whiteKing);
                        ChessPiece* rook = board[7][0].GetPiece();

                        board[7][3].SetPiece(rook);
                        board[7][0].Clear();
                        board[7][2].SetPiece(whiteKing);
                        board[7][4].Clear();

                        rook->setPosition(sf::Vector2i(7, 3));
                        whiteKing->setPosition(sf::Vector2i(7, 2));

                        if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) {
                            std::string posKey = whiteKing->getType() + std::to_string(whiteKing->getPosition().x) + std::to_string(whiteKing->getPosition().y);
                            legalMoves[posKey].push_back(sf::Vector2i(7, 0));
                            legalMoves[posKey].push_back(sf::Vector2i(7, 1));
                            legalMoves[posKey].push_back(sf::Vector2i(7, 2));
                        }

                        board[7][3].Clear();
                        board[7][0].SetPiece(rook);
                        board[7][2].Clear();
                        board[7][4].SetPiece(whiteKing);

                        rook->setPosition(sf::Vector2i(7, 0));
                        whiteKing->setPosition(sf::Vector2i(7, 4));

                    }
                }
            }
            if (!passedFirstCheck) {
                board[7][3].Clear();
                board[7][4].SetPiece(whiteKing);
            }
            if (!passedSecondCheck) {
                board[7][2].Clear();
                board[7][4].SetPiece(whiteKing);
            }
            if (!passedThirdCheck) {
                board[7][1].Clear();
                board[7][4].SetPiece(whiteKing);
            }
        }
    }

    ChessPiece* blackKing = board[0][4].GetPiece();
    if (blackKing != nullptr && blackKing->getColor() == 'B' && blackKing->getType() == "K" && !whitesMove && !blackKing->getHasMoved()) {
        // King-side castling
        if (board[0][7].GetPiece() != nullptr && board[0][7].GetPiece()->getType() == "R" &&
            board[0][7].GetPiece()->getColor() == 'B' && !board[0][7].GetPiece()->getHasMoved() &&
            board[0][6].GetPiece() == nullptr && board[0][5].GetPiece() == nullptr) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            board[0][4].Clear();
            board[0][5].SetPiece(blackKing);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[0][5].Clear();
                board[0][6].SetPiece(blackKing);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[0][6].Clear();
                    board[0][4].SetPiece(blackKing);
                    ChessPiece* rook = board[0][7].GetPiece();

                    board[0][5].SetPiece(rook);
                    board[0][7].Clear();
                    board[0][6].SetPiece(blackKing);
                    board[0][4].Clear();

                    rook->setPosition(sf::Vector2i(0, 5));
                    blackKing->setPosition(sf::Vector2i(0, 6));

                    if (!checkForCheckmateOrCheck(!whitesMove, gameState, true) && !checkForStalemate(!whitesMove, gameState, true)) {
                        std::string posKey = blackKing->getType() + std::to_string(blackKing->getPosition().x) + std::to_string(blackKing->getPosition().y);
                        legalMoves[posKey].push_back(sf::Vector2i(0, 6));
                        legalMoves[posKey].push_back(sf::Vector2i(0, 7));
                    }

                    board[0][5].Clear();
                    board[0][7].SetPiece(rook);
                    board[0][6].Clear();
                    board[0][4].SetPiece(blackKing);

                    rook->setPosition(sf::Vector2i(0, 7));
                    blackKing->setPosition(sf::Vector2i(0, 4));
                }
            }
            if (!passedFirstCheck) {
                board[0][5].Clear();
                board[0][4].SetPiece(blackKing);
            }
            if (!passedSecondCheck) {
                board[0][6].Clear();
                board[0][4].SetPiece(blackKing);
            }
        }
        if (board[0][0].GetPiece() != nullptr && board[0][0].GetPiece()->getType() == "R" &&
            board[0][0].GetPiece()->getColor() == 'B' && !board[0][0].GetPiece()->getHasMoved() &&
            board[0][1].GetPiece() == nullptr && board[0][2].GetPiece() == nullptr && board[0][3].GetPiece() == nullptr) {

            // Check if the king would be moving through check or not
            bool passedFirstCheck = false;
            bool passedSecondCheck = false;
            bool passedThirdCheck = false;
            board[0][4].Clear();
            board[0][3].SetPiece(blackKing);
            if (!isKingInCheck(!whitesMove, board)) {
                passedFirstCheck = true;
                board[0][3].Clear();
                board[0][2].SetPiece(blackKing);
                if (!isKingInCheck(!whitesMove, board)) {
                    passedSecondCheck = true;
                    board[0][2].Clear();
                    board[0][1].SetPiece(blackKing);
                    if (!isKingInCheck(!whitesMove, board)) {
                        passedThirdCheck = true;
                        board[0][1].Clear();
                        board[0][4].SetPiece(blackKing);
                        ChessPiece* rook = board[0][0].GetPiece();

                        board[0][3].SetPiece(rook);
                        board[0][0].Clear();
                        board[0][2].SetPiece(blackKing);
                        board[0][4].Clear();

                        rook->setPosition(sf::Vector2i(0, 3));
                        blackKing->setPosition(sf::Vector2i(0, 2));

                        if (!checkForCheckmateOrCheck(!whitesMove, gameState, false) && !checkForStalemate(!whitesMove, gameState, false)) {
                            std::string posKey = blackKing->getType() + std::to_string(blackKing->getPosition().x) + std::to_string(blackKing->getPosition().y);
                            legalMoves[posKey].push_back(sf::Vector2i(0, 0));
                            legalMoves[posKey].push_back(sf::Vector2i(0, 1));
                            legalMoves[posKey].push_back(sf::Vector2i(0, 2));
                        }

                        board[0][3].Clear();
                        board[0][0].SetPiece(rook);
                        board[0][2].Clear();
                        board[0][4].SetPiece(blackKing);

                        rook->setPosition(sf::Vector2i(0, 0));
                        blackKing->setPosition(sf::Vector2i(0, 4));

                    }
                }
            }
            if (!passedFirstCheck) {
                board[0][3].Clear();
                board[0][4].SetPiece(blackKing);
            }
            if (!passedSecondCheck) {
                board[0][2].Clear();
                board[0][4].SetPiece(blackKing);
            }
            if (!passedThirdCheck) {
                board[0][1].Clear();
                board[0][4].SetPiece(blackKing);
            }
        }
    }
}

// PRE: origPiece is a ChessPiece object that is not null,
// POST: updates the most recently moved piece as the last moved piece
//       (used for en passant).
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

// PRE: piecePos is a sf::Vector2i representing the position of the piece being grabbed.
// POST: RV is pointer to ChessPiece object, can be null or defined.
ChessPiece* Board::GetPiece(sf::Vector2i piecePos) {
    return board[piecePos.x][piecePos.y].GetPiece();
}

// PRE: mousePosition is a sf::Vector2i representing where on the board a mouse click was registered
//      windowWidth is an int representing the width of the window.
// POST: RV is sf::Vector2i representing a square on the board.
sf::Vector2i Board::GetBoardPosition(const sf::Vector2i& mousePosition, int windowWidth) {
    int cellSize = windowWidth / 8;

    int col = mousePosition.x / cellSize;
    int row = mousePosition.y / cellSize;

    return sf::Vector2i(row, col);
}

// PRE: whitesMove is a bool that represents whos turn it is,
//      gameState is an int representing the current state of the game.
// POST: RV is either true (Checkmate or check) or false (game in progress).
bool Board::checkForCheckmateOrCheck(bool whitesMove, int& gameState, bool insideCheckFunction) {
    std::unordered_map<std::string, std::vector<sf::Vector2i>> otherColorLegalMoves = getLegalMoves(!whitesMove);

    if (isKingInCheck(whitesMove, board)) {
        bool noLegalMoves = true;

        for (const auto& entry : otherColorLegalMoves) {
            if (!entry.second.empty()) {
                noLegalMoves = false;
                break;
            }
        }

        if (noLegalMoves) {
            if (!insideCheckFunction) {
                gameState = 1;
                checkSound.play();
                gameEndSound.play();
            }
        }
        else {
            if (!insideCheckFunction) {
                checkSound.play();
            }
        }
        return (true);
    }
    return (false);
}

// PRE: whitesMove is a bool that represents whos turn it is,
//      gameState is an int representing the current state of the game.
// POST: RV is either true (stalemate) or false (game in progress).
bool Board::checkForStalemate(bool whitesMove, int& gameState, bool insideCheckFunction) {
    std::unordered_map<std::string, std::vector<sf::Vector2i>> otherColorLegalMoves = getLegalMoves(!whitesMove);

    if (!isKingInCheck(whitesMove, board)) {
        bool noLegalMoves = true;

        for (const auto& entry : otherColorLegalMoves) {
            if (!entry.second.empty()) {
                noLegalMoves = false;
                break;
            }
        }

        if (noLegalMoves) {
            if (!insideCheckFunction) {
                gameState = 3;
                gameEndSound.play();
            }
            return (true);
        }
    }
    return (false);
}

// PRE: whitesMove is a bool that represents whos turn it is,
//      gameState is an int representing the current state of the game.
// POST: RV is either true (draw) or false (game in progress).
bool Board::checkForDrawByInsufficientMaterial(int& gameState) {

    std::unordered_map<std::string, int> whitePieces;
    std::unordered_map<std::string, int> blackPieces;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            if (piece != nullptr) {
                if (piece->getColor() == 'W') {
                    whitePieces[piece->getType()]++;
                }
                else {
                    blackPieces[piece->getType()]++;
                }
            }
        }
    }

    // Check for King vs King
    bool drawByKingVsKing =
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 0 && blackPieces["B"] == 0 &&
        whitePieces["N"] == 0 && blackPieces["N"] == 0;

    // Check for King and Bishop vs king
    bool drawByKingBishopVsKingWhite = 
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 1 && blackPieces["B"] == 0 &&
        whitePieces["N"] == 0 && blackPieces["N"] == 0;

    bool drawByKingBishopVsKingBlack =
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 0 && blackPieces["B"] == 1 &&
        whitePieces["N"] == 0 && blackPieces["N"] == 0;

    // Check for King and Knight vs king
    bool drawByKingKnightVsKingWhite =
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 0 && blackPieces["B"] == 0 &&
        whitePieces["N"] == 1 && blackPieces["N"] == 0;

    bool drawByKingKnightVsKingBlack =
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 0 && blackPieces["B"] == 0 &&
        whitePieces["N"] == 0 && blackPieces["N"] == 1;

    // Check for King and Bishop vs King and Bishop
    bool drawByKingBishopVsKingBishop =
        whitePieces["R"] == 0 && blackPieces["R"] == 0 &&
        whitePieces["P"] == 0 && blackPieces["P"] == 0 &&
        whitePieces["K"] == blackPieces["K"] &&
        whitePieces["Q"] == 0 && blackPieces["Q"] == 0 &&
        whitePieces["B"] == 1 && blackPieces["B"] == 1 &&
        whitePieces["N"] == 0 && blackPieces["N"] == 0;

    if (drawByKingVsKing ||
        drawByKingBishopVsKingWhite ||
        drawByKingBishopVsKingBlack ||
        drawByKingKnightVsKingWhite ||
        drawByKingKnightVsKingBlack ||
        drawByKingBishopVsKingBishop) {

        gameEndSound.play();
        gameState = 2;
        return (true);
    }

    return (false);
}

// PRE: 
// POST: RV = string representing the positions of pieces on the board
std::string Board::generateBoardState() {
    std::string state;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board[row][col].GetPiece();
            if (piece != nullptr) {
                state += piece->getType();
                state += std::to_string(row) + std::to_string(col);
            }
        }
    }
    return (state);
}

// PRE: 
// POST: positionCounts is incremented at the appropriate location matching the board's position
void Board::updatePositionCounts() {
    std::string currentState = generateBoardState();
    positionCounts[currentState]++;
}

// PRE: gameState is an int representing the current state of the game.
// POST: RV is either true (draw) or false (game in progress).
bool Board::checkForDrawByRepetition(int& gameState) {
    std::string currentState = generateBoardState();
    auto it = positionCounts.find(currentState);
    if (it != positionCounts.end() && it->second >= 3) {
        gameState = 4;
        gameEndSound.play();
        return (true);
    }
    return (false);
}

// PRE: gameState is an int representing the current state of the game.
// POST: RV is either true (draw) or false (game in progress).
bool Board::checkForDrawByFiftyMoveRule(int& gameState) {
    if (fiftyMoveCounter >= 100) {
        gameState = 5;
        gameEndSound.play();
        return (true);
    }
    return (false);
}

// PRE: window is a sf::RenderWindow which is the window where the board and pieces are displayed,
// POST: logical display of board is displayed graphically to the window.
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
            if (piece != nullptr) {
                piece->getSprite().setPosition((piece->getPosition().y * squareSize) + piece->getOffsetX(), (piece->getPosition().x * squareSize) + piece->getOffsetY());
                window.draw(piece->getSprite());
            }
        }
    }
}

// PRE: board is a Board type object representing the internal state of the board.
// POST: board's internal state is displayed to the terminal.
//      (useful for debugging).
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

// PRE:
// POST: All pieces are placed on their defualt squares and initilized correctly.
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

// PRE: window is an already initialized and open sf::RenderWindow object representing the game window,
//      transparency is a BYTE value (0-255) representing the desired level of transparency for the window, 
//      where 0 is fully transparent and 255 is fully opaque.
// POST: The window's transparency level is set according to transparency,
//       the window remains functional, continues to render its contents, and responds to user interactions.
//       the transparency value does not affect the contents within the window, only the window itself, 
//       making it blend into the desktop with the set transparency.
void Board::makeWindowTransparent(sf::RenderWindow& window, BYTE transparency) {
    HWND hwnd = window.getSystemHandle();
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, transparency, LWA_ALPHA);
}