#include "SettingsMenu.h"
#include "WordManager.h"
#include "WindowFunction.h"
#include <iostream>

SettingsMenu::SettingsMenu(float width, float height, const sf::Font& font)
        : font(font), selectedOptionIndex(-1),  selectedFontIndex(0) {

    if (!easyFont.loadFromFile("help/easy.ttf") ||
        !middleFont.loadFromFile("help/middle.ttf") ||
        !hardFont.loadFromFile("help/hardfont.ttf")) {
        std::cerr << "Failed to load one or more fonts" << std::endl;
    }

    // Створення кнопок для вибору шрифту
    std::vector<std::string> fontNames = {"Easy", "Middle", "Hard"};
    std::vector<sf::Font*> fontPointers = {&easyFont, &middleFont, &hardFont};
    float fontCenterX = (width / 4.0f) * 3.5;
    float fontStartY = height * 0.4;


    for (int i = 0; i < fontNames.size(); ++i) {
        sf::Text text;
        text.setFont(*fontPointers[i]);
        text.setString(fontNames[i]);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        fontOptions.push_back(text);

    }

    for (int i = 0; i < fontOptions.size(); ++i) {
        sf::FloatRect textBounds = fontOptions[i].getLocalBounds();
        fontOptions[i].setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        fontOptions[i].setPosition(fontCenterX, fontStartY + i * 125);
    }


    selectedFontIndex = 1;
    currentFont = "Middle";
    fontOptions[selectedFontIndex].setFillColor(sf::Color::Red);


    std::vector<std::string> options = { "Beginner", "Advanced", "Pro" };
    for (const auto& option : options) {
        sf::Text text;
        text.setFont(font);
        text.setString(option);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        settingsOptions.push_back(text);
    }


    float speedCenterX = (width / 4.0f) * 0.25;
    float speedStartY = height * 0.4;

    for (int i = 0; i < settingsOptions.size(); ++i) {
        sf::FloatRect textBounds = settingsOptions[i].getLocalBounds();
        settingsOptions[i].setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        settingsOptions[i].setPosition(speedCenterX, speedStartY + i * 125); // Збільшення Y на кожен наступний режим
    }




    backButton.setFont(font);
    backButton.setString("Back");
    backButton.setCharacterSize(50);
    backButton.setFillColor(sf::Color::White);
    backButton.setOutlineColor(sf::Color::Black);
    backButton.setOutlineThickness(3);
    sf::FloatRect backButtonBounds = backButton.getLocalBounds();
    backButton.setPosition((width / 2) - ((backButton.getGlobalBounds().width / 2) + 40), height * 0.85);

    fontsText.setFont(font);
    fontsText.setString("Font:");
    fontsText.setCharacterSize(60);
    fontsText.setFillColor(sf::Color::Blue);
    fontsText.setPosition((width / 4.0f) * 3.5, height * 0.2);

    optionsText.setFont(font);
    optionsText.setString("Speed:");
    optionsText.setCharacterSize(60);
    optionsText.setFillColor(sf::Color::Blue);
    optionsText.setPosition((width / 4.0f) * 0.25, height * 0.2);


    selectedOptionIndex = 1;
    currentDifficulty = "Advanced";
    settingsOptions[selectedOptionIndex].setFillColor(sf::Color::Red);
}

void SettingsMenu::draw(sf::RenderWindow& window) {
    for (const auto& button : settingsOptions) {
        window.draw(button);
    }
    for (const auto& fontButton : fontOptions) {
        window.draw(fontButton);
    }
    window.draw(backButton);
    window.draw(fontsText);
    window.draw(optionsText);
}


void SettingsMenu::handleInput(sf::Event& event, int& currentScreen, WordManager& wordManager) {
    if (event.type == sf::Event::MouseButtonReleased) {
        for (int i = 0; i < settingsOptions.size(); ++i) {
            if (settingsOptions[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Option " << i << " selected" << std::endl; // Додано для відладки
                selectedOptionIndex = i;
                for (int j = 0; j < settingsOptions.size(); ++j) {
                    if (j == selectedOptionIndex) {
                        settingsOptions[j].setFillColor(sf::Color::Red);
                    } else {
                        settingsOptions[j].setFillColor(sf::Color::Black);
                    }
                }
                if (i == 0) { // Beginner
                    wordManager.setSpeedMultiplier(0.75f);
                    wordManager.setSpawnInterval(2.0);
                    currentDifficulty = "Beginner";
                } else if (i == 1) { // Advanced
                    wordManager.setSpeedMultiplier(1.0f);
                    wordManager.setSpawnInterval(1.75);

                    currentDifficulty = "Advanced";
                } else if (i == 2) { // Pro
                    wordManager.setSpeedMultiplier(1.75f);
                    wordManager.setSpawnInterval(1.5);

                    currentDifficulty = "Pro";
                }
            }
        }

        for (int i = 0; i < fontOptions.size(); ++i) {
            if (fontOptions[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Option " << i << " selected" << std::endl; // Додано для відладки
                selectedFontIndex = i;
                for (int j = 0; j < fontOptions.size(); ++j) {
                    if (j == selectedFontIndex) {
                        fontOptions[j].setFillColor(sf::Color::Red);
                    } else {
                        fontOptions[j].setFillColor(sf::Color::Black);
                    }
                }
                if (i == 0) { // Easy
                    fontOptions[i].setFont(easyFont);
                    wordManager.setFont(easyFont);
                    currentFont = "Easy";
                } else if (i == 1) { // Middle
                    wordManager.setFont(middleFont);
                    fontOptions[i].setFont(middleFont);
                    currentFont = "Middle";
                } else if (i == 2) { // Hard
                    wordManager.setFont(hardFont);
                    fontOptions[i].setFont(hardFont);
                    currentFont = "Hard";
                }
            }
        }



        if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            std::cout << "Back button pressed" << std::endl; // Додано для відладки
            currentScreen = static_cast<int>(Window::Screen::Menu);
        }
    }
}

int SettingsMenu::getPressedItem(int mouseX, int mouseY) {
    for (size_t i = 0; i < settingsOptions.size(); ++i) {
        if (settingsOptions[i].getGlobalBounds().contains(mouseX, mouseY)) {
            return i;
        }
    }
    return -1;
}



std::string SettingsMenu::getCurrentDifficulty() const {
    return currentDifficulty;
}

std::string SettingsMenu::getCurrentFont() const {
    return currentFont;
}




