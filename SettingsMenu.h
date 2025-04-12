#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "WordManager.h"

class SettingsMenu {
public:
    SettingsMenu(float width, float height, const sf::Font& font);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, int& currentScreen, WordManager& wordManager);
    int getPressedItem(int mouseX, int mouseY);


    std::string getCurrentDifficulty() const;
    std::string getCurrentFont() const;



private:
    sf::Font font;

    std::vector<sf::Text> settingsOptions;
    std::vector<sf::Text> fontOptions;

    int selectedOptionIndex;
    int selectedFontIndex;

    sf::Text backButton;

    std::string currentDifficulty;
    std::string currentFont;


    sf::Font easyFont, middleFont, hardFont;

    sf::Text fontsText;
    sf::Text optionsText;
};