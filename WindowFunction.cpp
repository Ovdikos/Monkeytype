#include "WindowFunction.h"
#include <iostream>





Window::Window(const std::string& wordsFile)
        : window(sf::VideoMode::getDesktopMode(), "Monkey Typer", sf::Style::Fullscreen),
          hud(font), wordManager(wordsFile, hud, window), menu(window.getSize().x, window.getSize().y),
          settingsMenu(window.getSize().x, window.getSize().y, font), recordsMenu(window.getSize().x, window.getSize().y, font),
          currentScreen(static_cast<int>(Screen::Menu)), enteringName(false), recordLimitReached(false)
          {
    if (!font.loadFromFile("help/font.ttf")) {
        std::cerr << "Failed to load font\n";
    }


    if (!menuBackgroundTexture.loadFromFile("help/background.jpg")) {
        std::cerr << "Failed to load menu background\n";
    }


    if (!gameBackgroundTexture.loadFromFile("help/gameground.jpg")) {
        std::cerr << "Failed to load game background\n";
    }

    if (!gameOverBackgroundTexture.loadFromFile("help/gameover.jpg")) {
        std::cerr << "Failed to load game over background\n";
    }

    if (!settingsBackgroundTexture.loadFromFile("help/settings.jpg")) {
        std::cerr << "Failed to load settings background\n";
    }
    if (!recordsBackgroundTexture.loadFromFile("help/records.jpg")) {
        std::cerr << "Failed to load records background\n";
    }
    background.setTexture(menuBackgroundTexture);


    gameOverText.setFont(font);
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 3);


    playAgainText.setFont(font);
    playAgainText.setCharacterSize(50);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setString("Play Again");
    playAgainText.setPosition(window.getSize().x / 2 - playAgainText.getGlobalBounds().width / 2, window.getSize().y / 2);


    saveResultsButton.setFont(font);
    saveResultsButton.setCharacterSize(50);
    saveResultsButton.setFillColor(sf::Color::White);
    saveResultsButton.setString("Save Results");
    saveResultsButton.setPosition(window.getSize().x / 2 - saveResultsButton.getGlobalBounds().width / 2, window.getSize().y / 2 + 100);

    menuButton.setFont(font);
    menuButton.setCharacterSize(50);
    menuButton.setFillColor(sf::Color::Red);
    menuButton.setString("Menu");
    menuButton.setPosition(window.getSize().x / 2 - menuButton.getGlobalBounds().width / 2, window.getSize().y * 0.90 );

    inputNamePromptText.setFont(font);
    inputNamePromptText.setCharacterSize(50);
    inputNamePromptText.setFillColor(sf::Color::White);
    inputNamePromptText.setString("Please Input Your Name:");
    inputNamePromptText.setPosition(window.getSize().x / 2, window.getSize().y * 0.70);
    inputNamePromptText.setOrigin(inputNamePromptText.getLocalBounds().width / 2, inputNamePromptText.getLocalBounds().height / 2);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(50);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(window.getSize().x / 2, window.getSize().y * 0.75);
    playerNameText.setOrigin(playerNameText.getLocalBounds().width / 2, playerNameText.getLocalBounds().height / 2);


    recordLimitReachedText.setFont(font);
    recordLimitReachedText.setCharacterSize(50);
    recordLimitReachedText.setFillColor(sf::Color::Red);
    recordLimitReachedText.setString("You have reached the limit of records");
    recordLimitReachedText.setPosition(window.getSize().x / 2, window.getSize().y * 0.73);
    recordLimitReachedText.setOrigin(recordLimitReachedText.getLocalBounds().width / 2, recordLimitReachedText.getLocalBounds().height / 2);
}



void Window::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        sf::Time deltaTime = clock.restart();
        update(deltaTime);
        render();
    }
}


void Window::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            currentScreen = static_cast<int>(Screen::Menu);
            background.setTexture(menuBackgroundTexture);
        }

        if (currentScreen == static_cast<int>(Screen::Menu)) {
            if (event.type == sf::Event::MouseButtonReleased) {
                int pressedItem = menu.getPressedItem(event.mouseButton.x, event.mouseButton.y);
                if (pressedItem == 0) {
                    currentScreen = static_cast<int>(Screen::Game);
                    background.setTexture(gameBackgroundTexture);
                    hud.reset();
                    wordManager.reset();
                } else if (pressedItem == 1) {
                    currentScreen = static_cast<int>(Screen::Settings);
                    background.setTexture(settingsBackgroundTexture);
                } else if (pressedItem == 2) {
                    currentScreen = static_cast<int>(Screen::Records);
                    background.setTexture(recordsBackgroundTexture);
                    recordsMenu.loadRecords("help/records.txt");
                } else if (pressedItem == 3) {
                    window.close();
                }
            }
        } else if (currentScreen == static_cast<int>(Screen::Game)) {
            wordManager.handleInput(event);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Add) {
                    wordManager.setSpeedMultiplier(wordManager.getSpeedMultiplier() + 0.25f);
                } else if (event.key.code == sf::Keyboard::Subtract) {
                    wordManager.setSpeedMultiplier(wordManager.getSpeedMultiplier() - 0.25f);
                }
            }
        } else if (currentScreen == static_cast<int>(Screen::Settings)) {
            settingsMenu.handleInput(event, currentScreen, wordManager);
            if (currentScreen == static_cast<int>(Screen::Menu)) {
                background.setTexture(menuBackgroundTexture);
            }
        } else if (currentScreen == static_cast<int>(Screen::GameOver)) {
            if (event.type == sf::Event::MouseButtonReleased) {
                if (playAgainText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentScreen = static_cast<int>(Screen::Game);
                    background.setTexture(gameBackgroundTexture);
                    hud.reset();
                    wordManager.reset();
                } else if (saveResultsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !enteringName) {
                    if (recordsMenu.hasReachedRecordLimit("help/records.txt", 15)) {
                        inputNamePromptText.setString("You have reached the limit of records");
                    } else {
                        enteringName = true;
                    }
                } else if (menuButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentScreen = static_cast<int>(Screen::Menu);
                    enteringName = false;
                    background.setTexture(menuBackgroundTexture);
                }
            }
            if (enteringName && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\r') {
                    recordsMenu.saveRecord("Player: " + playerName, hud.getCorrectCount(), settingsMenu.getCurrentDifficulty(), settingsMenu.getCurrentFont());
                    playerName.clear();
                    enteringName = false;
                    currentScreen = static_cast<int>(Screen::Records);
                    recordsMenu.loadRecords("help/records.txt");
                    background.setTexture(recordsBackgroundTexture);
                } else if (event.text.unicode == '\b') {
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                } else {
                    playerName += static_cast<char>(event.text.unicode);
                }
                playerNameText.setString(playerName);
                playerNameText.setOrigin(playerNameText.getLocalBounds().width / 2, playerNameText.getLocalBounds().height / 2);
                playerNameText.setPosition(window.getSize().x / 2, window.getSize().y * 0.75);
            }
        } else if (currentScreen == static_cast<int>(Screen::Records)) {
            if (event.type == sf::Event::MouseButtonReleased) {
                if (recordsMenu.getBackButtonBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentScreen = static_cast<int>(Screen::Menu);
                    background.setTexture(menuBackgroundTexture);
                }
            }
        }
    }
}



void Window::update(sf::Time deltaTime) {
    if (currentScreen == static_cast<int>(Screen::Game)) {
        wordManager.update(deltaTime.asSeconds());
        if (hud.getIncorrectCount() >= 5) {
            currentScreen = static_cast<int>(Screen::GameOver);
            background.setTexture(gameOverBackgroundTexture);
        }
    }
}

void Window::render() {
    window.clear();
    window.draw(background);
    if (currentScreen == static_cast<int>(Screen::Menu)) {
        menu.draw(window);
    } else if (currentScreen == static_cast<int>(Screen::Game)) {
        wordManager.render(window);
        hud.render(window);
    } else if (currentScreen == static_cast<int>(Screen::Settings)) {
        settingsMenu.draw(window);
    } else if (currentScreen == static_cast<int>(Screen::GameOver)) {
        window.draw(gameOverText);
        window.draw(playAgainText);
        window.draw(saveResultsButton);
        window.draw(menuButton);
        if (enteringName) {
            window.draw(inputNamePromptText);
            window.draw(playerNameText);
        }
        if (recordsMenu.recordsChanged) {
            if (!recordsBackgroundTexture.loadFromFile("help/happyrecords.jpg")) {
                std::cerr << "Failed to load records background\n";
            } else {
                background.setTexture(recordsBackgroundTexture);
            }
            recordsMenu.recordsChanged = false;
        }
        if (recordLimitReached) {
            window.draw(recordLimitReachedText);
        }
    } else if (currentScreen == static_cast<int>(Screen::Records)) {
        recordsMenu.draw(window);
    }
    window.display();
}

