#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "WordManager.h"

class SettingsMenu {
public:
    SettingsMenu(float width, float height, const sf::Font& font); // ініціалізує меню налаштувань з певною шириною, висотою та шрифтом.
    void draw(sf::RenderWindow& window); // Відмальовує елементи меню налаштувань у вікні.
    void handleInput(sf::Event& event, int& currentScreen, WordManager& wordManager); // Обробляє вхідні події від користувача (наприклад, кліки мишею) та взаємодіє з іншими компонентами гри.
    int getPressedItem(int mouseX, int mouseY); //  Визначає, який елемент меню було натиснуто, використовуючи координати миші.


    std::string getCurrentDifficulty() const; // Повертає поточний рівень складності гри.
    std::string getCurrentFont() const; // Повертає назву поточного шрифту.



private:
    sf::Font font;

    // Масиви текстових елементів, що відображають налаштування та вибір шрифтів відповідно.
    std::vector<sf::Text> settingsOptions;
    std::vector<sf::Text> fontOptions;

    // Індекси обраних налаштувань і шрифтів.
    int selectedOptionIndex;
    int selectedFontIndex;

    sf::Text backButton;

    // Змінні для зберігання поточних налаштувань складності та шрифту.
    std::string currentDifficulty;
    std::string currentFont;


    sf::Font easyFont, middleFont, hardFont;

    // Текстові мітки для відображення заголовків секцій налаштувань та шрифтів.
    sf::Text fontsText;
    sf::Text optionsText;
};