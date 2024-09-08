#include "mainFunctions.hpp"

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
void mainLoop(sf::RenderWindow& window, bool clickProcessed, Board& board, sf::Vector2i selectedPiece, bool whitesMove, int gameState, sf::Sound& gameStartSound, sf::Font font, int squareSize) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

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
                            selectedPiece = sf::Vector2i(-1, -1); // Reset selection after move
                        }
                    }
                    clickProcessed = true;
                    board.DisplayBoard(board);
                }
            }
        }
        clickProcessed = false;

        drawLettersNumbersAndSquares(font, squareSize, window);
        board.drawBoard(window);
        window.display();

        // Check if checkmate or stalemate occurred
        checkForCheckmate(gameState, window, whitesMove, board, gameStartSound);

        checkForStalemate(gameState, window, whitesMove, board, gameStartSound);
    }
}