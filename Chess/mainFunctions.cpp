#include "mainFunctions.hpp"

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
                        if (board.GetPiece(boardPosition) != NULL) {
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