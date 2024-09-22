#include "mainFunctions.hpp"
#include <iostream>

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showCheckmatePopup(bool& resetGame, bool& quitGame, bool whitesMove) {
    // Create a pop-up window
    sf::RenderWindow popup(sf::VideoMode(300, 200), "Checkmate", sf::Style::None);

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("assets/RobotoCondensed-Black.ttf")) {
        // Handle font loading error if necessary
        return;
    }

    // Create "Quit" button
    sf::RectangleShape quitButton(sf::Vector2f(120, 50));
    quitButton.setPosition(30, 120);
    quitButton.setFillColor(sf::Color::Red);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(120, 50));
    playAgainButton.setPosition(150, 120);
    playAgainButton.setFillColor(sf::Color::Green);

    // Create text labels for buttons
    sf::Text quitText("Quit", font, 20);
    quitText.setPosition(60, 130);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setPosition(160, 130);

    // Create the main text displaying which color won
    std::string winningColor = whitesMove ? "Black" : "White";
    sf::Text mainText(winningColor + " Wins", font, 24);
    mainText.setPosition(50, 20);
    mainText.setFillColor(sf::Color::Black);

    // Create the smaller text for "wins by checkmate"
    sf::Text subText(winningColor + " wins by checkmate", font, 18);
    subText.setPosition(50, 60);
    subText.setFillColor(sf::Color::Black);

    // Main loop for the pop-up window
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.requestFocus();
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);

                // Check if "Quit" button is clicked
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    quitGame = true;
                    popup.close();
                }

                // Check if "Play Again" button is clicked
                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame = true;
                    popup.close();
                }
            }
        }

        popup.requestFocus();
        popup.clear(sf::Color::White);
        popup.draw(quitButton);
        popup.draw(playAgainButton);
        popup.draw(quitText);
        popup.draw(playAgainText);
        popup.draw(mainText);
        popup.draw(subText);
        popup.display();
    }
}

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showStaleMatePopup(bool& resetGame, bool& quitGame, bool whitesMove) {
    // Create a pop-up window
    sf::RenderWindow popup(sf::VideoMode(300, 200), "Stalemate", sf::Style::None);

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("assets/RobotoCondensed-Black.ttf")) {
        // Handle font loading error if necessary
        return;
    }

    // Create "Quit" button
    sf::RectangleShape quitButton(sf::Vector2f(120, 50));
    quitButton.setPosition(30, 120);
    quitButton.setFillColor(sf::Color::Red);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(120, 50));
    playAgainButton.setPosition(150, 120);
    playAgainButton.setFillColor(sf::Color::Green);

    // Create text labels for buttons
    sf::Text quitText("Quit", font, 20);
    quitText.setPosition(60, 130);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setPosition(160, 130);

    // Create the main text displaying which color won
    sf::Text mainText("Draw!", font, 24);
    mainText.setPosition(50, 20);
    mainText.setFillColor(sf::Color::Black);

    // Create the smaller text for "wins by checkmate"
    sf::Text subText("Game drawn by stalemate", font, 18);
    subText.setPosition(50, 60);
    subText.setFillColor(sf::Color::Black);

    // Main loop for the pop-up window
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.requestFocus();
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);

                // Check if "Quit" button is clicked
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    quitGame = true;
                    popup.close();
                }

                // Check if "Play Again" button is clicked
                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame = true;
                    popup.close();
                }
            }
        }

        popup.requestFocus();
        popup.clear(sf::Color::White);
        popup.draw(quitButton);
        popup.draw(playAgainButton);
        popup.draw(quitText);
        popup.draw(playAgainText);
        popup.draw(mainText);
        popup.draw(subText);
        popup.display();
    }
}

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showDrawByInsufficientMaterialPopup(bool& resetGame, bool& quitGame, bool whitesMove) {
    // Create a pop-up window
    sf::RenderWindow popup(sf::VideoMode(300, 200), "Draw", sf::Style::None);

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("assets/RobotoCondensed-Black.ttf")) {
        // Handle font loading error if necessary
        return;
    }

    // Create "Quit" button
    sf::RectangleShape quitButton(sf::Vector2f(120, 50));
    quitButton.setPosition(30, 120);
    quitButton.setFillColor(sf::Color::Red);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(120, 50));
    playAgainButton.setPosition(150, 120);
    playAgainButton.setFillColor(sf::Color::Green);

    // Create text labels for buttons
    sf::Text quitText("Quit", font, 20);
    quitText.setPosition(60, 130);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setPosition(160, 130);

    // Create the main text displaying which color won
    sf::Text mainText("Draw!", font, 24);
    mainText.setPosition(50, 20);
    mainText.setFillColor(sf::Color::Black);

    // Create the smaller text for "wins by checkmate"
    sf::Text subText("Game drawn by repition", font, 18);
    subText.setPosition(50, 60);
    subText.setFillColor(sf::Color::Black);

    // Main loop for the pop-up window
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.requestFocus();
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);

                // Check if "Quit" button is clicked
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    quitGame = true;
                    popup.close();
                }

                // Check if "Play Again" button is clicked
                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame = true;
                    popup.close();
                }
            }
        }

        popup.requestFocus();
        popup.clear(sf::Color::White);
        popup.draw(quitButton);
        popup.draw(playAgainButton);
        popup.draw(quitText);
        popup.draw(playAgainText);
        popup.draw(mainText);
        popup.draw(subText);
        popup.display();
    }
}

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showDrawByRepititionPopup(bool& resetGame, bool& quitGame, bool whitesMove) {
    // Create a pop-up window
    sf::RenderWindow popup(sf::VideoMode(300, 200), "Draw", sf::Style::None);

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("assets/RobotoCondensed-Black.ttf")) {
        // Handle font loading error if necessary
        return;
    }

    // Create "Quit" button
    sf::RectangleShape quitButton(sf::Vector2f(120, 50));
    quitButton.setPosition(30, 120);
    quitButton.setFillColor(sf::Color::Red);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(120, 50));
    playAgainButton.setPosition(150, 120);
    playAgainButton.setFillColor(sf::Color::Green);

    // Create text labels for buttons
    sf::Text quitText("Quit", font, 20);
    quitText.setPosition(60, 130);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setPosition(160, 130);

    // Create the main text displaying which color won
    sf::Text mainText("Draw!", font, 24);
    mainText.setPosition(50, 20);
    mainText.setFillColor(sf::Color::Black);

    // Create the smaller text for "wins by checkmate"
    sf::Text subText("Game drawn by repitition", font, 18);
    subText.setPosition(50, 60);
    subText.setFillColor(sf::Color::Black);

    // Main loop for the pop-up window
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.requestFocus();
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);

                // Check if "Quit" button is clicked
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    quitGame = true;
                    popup.close();
                }

                // Check if "Play Again" button is clicked
                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame = true;
                    popup.close();
                }
            }
        }

        popup.requestFocus();
        popup.clear(sf::Color::White);
        popup.draw(quitButton);
        popup.draw(playAgainButton);
        popup.draw(quitText);
        popup.draw(playAgainText);
        popup.draw(mainText);
        popup.draw(subText);
        popup.display();
    }
}

// PRE: resetGame is a boolean value that is true iff the user clicks the "play again" button,
//		quitGame is a boolean value that is true iff the user clicks the "quit" button,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move
// POST: the game is either reset or closed.
void showDrawByFiftyMoveRulePopup(bool& resetGame, bool& quitGame, bool whitesMove) {
    // Create a pop-up window
    sf::RenderWindow popup(sf::VideoMode(300, 200), "Draw", sf::Style::None);

    // Load font for text
    sf::Font font;
    if (!font.loadFromFile("assets/RobotoCondensed-Black.ttf")) {
        // Handle font loading error if necessary
        return;
    }

    // Create "Quit" button
    sf::RectangleShape quitButton(sf::Vector2f(120, 50));
    quitButton.setPosition(30, 120);
    quitButton.setFillColor(sf::Color::Red);

    // Create "Play Again" button
    sf::RectangleShape playAgainButton(sf::Vector2f(120, 50));
    playAgainButton.setPosition(150, 120);
    playAgainButton.setFillColor(sf::Color::Green);

    // Create text labels for buttons
    sf::Text quitText("Quit", font, 20);
    quitText.setPosition(60, 130);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setPosition(160, 130);

    // Create the main text displaying which color won
    sf::Text mainText("Draw!", font, 24);
    mainText.setPosition(50, 20);
    mainText.setFillColor(sf::Color::Black);

    // Create the smaller text for "wins by checkmate"
    sf::Text subText("Game drawn by fifty move rule", font, 18);
    subText.setPosition(50, 60);
    subText.setFillColor(sf::Color::Black);

    // Main loop for the pop-up window
    while (popup.isOpen()) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popup.requestFocus();
                popup.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);

                // Check if "Quit" button is clicked
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    quitGame = true;
                    popup.close();
                }

                // Check if "Play Again" button is clicked
                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame = true;
                    popup.close();
                }
            }
        }

        popup.requestFocus();
        popup.clear(sf::Color::White);
        popup.draw(quitButton);
        popup.draw(playAgainButton);
        popup.draw(quitText);
        popup.draw(playAgainText);
        popup.draw(mainText);
        popup.draw(subText);
        popup.display();
    }
}

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: checkmate is checked for, either showCheckmatePopup is called, or
//		 the game continues
void checkForCheckmate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound) {
    if (gameState == 1) {

        bool resetGame = false;
        bool quitGame = false;
        window.setActive(false);
        showCheckmatePopup(resetGame, quitGame, whitesMove);

        if (quitGame) {
            window.close();
        }
        else if (resetGame) {
            board.resetBoard();
            whitesMove = true;
            gameState = 0;
            gameStartSound.play();
        }
        window.setActive(true);
        window.requestFocus();
    }
}

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: stalemate is checked for, either showStalematePopup is called, or
//		 the game continues
void checkForStalemate(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound) {
    if (gameState == 3) {

        bool resetGame = false;
        bool quitGame = false;
        window.setActive(false);
        showStaleMatePopup(resetGame, quitGame, whitesMove);

        if (quitGame) {
            window.close();
        }
        else if (resetGame) {
            board.resetBoard();
            whitesMove = true;
            gameState = 0;
            gameStartSound.play();
        }
        window.setActive(true);
        window.requestFocus();
    }
}

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: draw by insufficient material is checked for, either showDrawByInsufficientMaterialPopup is called,
//       or the game continues
void checkForDrawByInsufficientMaterial(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound) {
    if (gameState == 2) {

        bool resetGame = false;
        bool quitGame = false;
        window.setActive(false);
        showDrawByInsufficientMaterialPopup(resetGame, quitGame, whitesMove);

        if (quitGame) {
            window.close();
        }
        else if (resetGame) {
            board.resetBoard();
            whitesMove = true;
            gameState = 0;
            gameStartSound.play();
        }
        window.setActive(true);
        window.requestFocus();
    }
}

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: draw by repitition is checked for, either showDrawByRepititionPopup is called,
//       or the game continues
void checkForDrawByRepitition(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound) {
    if (gameState == 4) {

        bool resetGame = false;
        bool quitGame = false;
        window.setActive(false);
        showDrawByInsufficientMaterialPopup(resetGame, quitGame, whitesMove);

        if (quitGame) {
            window.close();
        }
        else if (resetGame) {
            board.resetBoard();
            whitesMove = true;
            gameState = 0;
            gameStartSound.play();
        }
        window.setActive(true);
        window.requestFocus();
    }
}

// PRE: gameState is an int that represents the current state of the game,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		gameStartSound is an sf::Sound that plays the game-start sound
// POST: draw by repitition is checked for, either showDrawByRepititionPopup is called,
//       or the game continues
void checkForDrawByFiftyMoveRule(int& gameState, sf::RenderWindow& window, bool& whitesMove, Board& board, sf::Sound& gameStartSound) {
    if (gameState == 5) {

        bool resetGame = false;
        bool quitGame = false;
        window.setActive(false);
        showDrawByFiftyMoveRulePopup(resetGame, quitGame, whitesMove);

        if (quitGame) {
            window.close();
        }
        else if (resetGame) {
            board.resetBoard();
            whitesMove = true;
            gameState = 0;
            gameStartSound.play();
        }
        window.setActive(true);
        window.requestFocus();
    }
}

// PRE: font is an sf::Font that determines the styling of the numbers and letters on the rows
//		and columns of the board,
//		squareSize is an int that represents the size of the squares on the board,
//		window is a sf::RenderWindow which is the window where the board and pieces are displayed,
// POST: squares are drawn to the board as well as colored,
//       letters 'a'-'h' are drawn on the bottom row of the board,
//		 numbers 1-7 are drawn on the 1st column of the board
void drawLettersNumbersAndSquares(sf::Font font, int squareSize, sf::RenderWindow& window) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);

            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color(227, 237, 246));
            }
            else {
                square.setFillColor(sf::Color(137, 173, 203));
            }

            window.draw(square);
        }
    }

    for (int row = 0; row < 8; ++row) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(8 - row));
        text.setCharacterSize(24);
        if (row % 2 == 0) {
            text.setFillColor(sf::Color(137, 173, 203));
        }
        else {
            text.setFillColor(sf::Color(227, 237, 246));
        }
        text.setPosition(5, row * squareSize);
        window.draw(text);
    }

    for (int col = 0; col < 8; ++col) {
        sf::Text text;
        text.setFont(font);
        text.setString(static_cast<char>('a' + col));
        text.setCharacterSize(24);
        if (col % 2 == 0) {
            text.setFillColor(sf::Color(227, 237, 246));
        }
        else {
            text.setFillColor(sf::Color(137, 173, 203));
        }
        text.setPosition(col * squareSize + 85, 770);
        window.draw(text);
    }
}

// PRE:
// POST:
void MarkybotVsMarkyBot(bool& whitesMove, Board& board, sf::RenderWindow& window ,int gameState, bool& clickProcessed, sf::Font font, int squareSize, sf::Sound& gameStartSound) {

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Find all legal moves
        std::unordered_map<std::string, std::vector<sf::Vector2i>> legalMoves = board.getLegalMoves(whitesMove);
        
        // Add castling to legal moves if it is possible
        board.addCastlingToLegalMoves(legalMoves, whitesMove, gameState);
        
        if (legalMoves.empty()) return;

        sf::sleep(sf::milliseconds(50));

        std::vector<std::pair<sf::Vector2i, sf::Vector2i>> allMoves;

        for (const auto& entry : legalMoves) {
            const std::string& piecePos = entry.first;
            const std::vector<sf::Vector2i>& moves = entry.second;

            std::string xStr = piecePos.substr(piecePos.length() - 2, 1);
            std::string yStr = piecePos.substr(piecePos.length() - 1, 1);

            int x = std::stoi(xStr);
            int y = std::stoi(yStr);

            
            sf::Vector2i startPos(x, y);

            for (const sf::Vector2i& endPos : moves) {
                allMoves.emplace_back(startPos, endPos);
            }
        }

        int randomMoveIndex = std::rand() % legalMoves.size();
        sf::Vector2i selectedPiece = allMoves[randomMoveIndex].first;
        sf::Vector2i toPos = allMoves[randomMoveIndex].second;

        board.MovePiece(selectedPiece, toPos, whitesMove, window, gameState);

        window.clear(sf::Color::White);  // Clear the window with a white background (or any desired color)
        drawLettersNumbersAndSquares(font, squareSize, window); // Redraw the labels and board setup
        board.drawBoard(window); // Draw the board and pieces
        window.display();

        checkForCheckmate(gameState, window, whitesMove, board, gameStartSound);

        checkForStalemate(gameState, window, whitesMove, board, gameStartSound);

        checkForDrawByInsufficientMaterial(gameState, window, whitesMove, board, gameStartSound);

        checkForDrawByRepitition(gameState, window, whitesMove, board, gameStartSound);

        checkForDrawByFiftyMoveRule(gameState, window, whitesMove, board, gameStartSound);
}

// PRE:
// POST:
void playerVsPlayer(bool clickProcessed, sf::Event event, sf::RenderWindow& window, Board& board, sf::Vector2i& selectedPiece, bool& whitesMove, int gameState, sf::Font font, sf::Sound gameStartSound, int squareSize) {
    if (!clickProcessed && event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2i boardPosition = board.GetBoardPosition(mousePosition, window.getSize().x);

            if (selectedPiece.x == -1 && selectedPiece.y == -1) {
                // First click: Select piece
                if (board.GetPiece(boardPosition) != nullptr) {
                    selectedPiece = boardPosition;
                }
            }
            else {
                // Second click: Attempt to move the piece

                if (board.MovePiece(selectedPiece, boardPosition, whitesMove, window, gameState)) {
                    window.clear(sf::Color::White);
                    drawLettersNumbersAndSquares(font, squareSize, window);
                    board.drawBoard(window);
                    window.display();

                    checkForCheckmate(gameState, window, whitesMove, board, gameStartSound);

                    checkForStalemate(gameState, window, whitesMove, board, gameStartSound);

                    checkForDrawByInsufficientMaterial(gameState, window, whitesMove, board, gameStartSound);

                    checkForDrawByRepitition(gameState, window, whitesMove, board, gameStartSound);

                    checkForDrawByFiftyMoveRule(gameState, window, whitesMove, board, gameStartSound);
                    selectedPiece = sf::Vector2i(-1, -1); // Reset selection after move
                }
            }
            clickProcessed = true;
            board.DisplayBoard(board);
        }
    }
}

// PRE: window is a sf::RenderWindow which is the window where the board and pieces are displayed,
//		clickProcessed is a boolean value asserting that only one click per turn is registered at a time,
//		board is a 8 x 8 matrix of Square objects representing the chess board,
//		selectedPiece is an sf::Vector2i that represents the square clicked on the board,
//		whitesMove is a boolean value that is true iff it is whites move and false iff
//		it is blacks move,
//		gameState is an int that represents the current state of the game,
//		gameStartSound is an sf::Sound that plays the game-start sound,
//		font is an sf::Font that determines the styling of the numbers and letters on the rows,
//		squareSize is an int that represents the size of the squares on the board
// POST: Pieces are drawn to the window, clicks are processed, as well as checks for checkmate,
//		 stalemate, and draw.
void mainLoop(sf::RenderWindow& window, bool clickProcessed, Board& board, sf::Vector2i selectedPiece, bool whitesMove, int gameState, sf::Sound& gameStartSound, sf::Font font, int squareSize, int gameType) {
    while (window.isOpen()) {
        sf::Event event;
        drawLettersNumbersAndSquares(font, squareSize, window);
        board.drawBoard(window);
        window.display();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (gameType == 0) {
                playerVsPlayer(clickProcessed, event, window, board, selectedPiece, whitesMove, gameState, font, gameStartSound, squareSize);
            }
        }
        
        if (!clickProcessed && gameState == 0 && gameType == 2) {
            MarkybotVsMarkyBot(whitesMove, board, window, gameState, clickProcessed, font, squareSize, gameStartSound);
        }
        clickProcessed = false;
    }
}