#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include "HUD.h"

class WordManager {
public:
    WordManager(const std::string &wordsFile, HUD &hud, sf::RenderWindow &window);
    void handleInput(sf::Event& event); // Обробляє введення користувача, перевіряє наявність введених слів серед активних.
    void update(float deltaTime); // Оновлює стан гри, зокрема переміщення слів та їх генерацію через певні інтервали часу.
    void render(sf::RenderWindow& window); //  Відмальовує всі слова, які зараз активні на екрані.
    void reset(); // Скидає всі параметри до початкових налаштувань, очищає список слів.

   // Методи для налаштування швидкості слова та інтервалу появи нових слів.
    void setSpeedMultiplier(float multiplier);
    void setSpawnInterval(float interval);


    void setFont(const sf::Font& font); // Оновлює шрифт для всіх текстових об'єктів.
    float getSpeedMultiplier() const; // Повертає поточний множник швидкості.


    //Ця структура дозволяє зв'язати текстовий об'єкт з його порядковим номером для легшого управління в контексті ігрової логіки,
    // наприклад, для відстеження порядку появи слів і прибирання слова після того, як воно було введено коректно.
private:
    struct WordText {
        sf::Text text; // Об'єкт тексту SFML, що зображує слово.
        int order; // Порядковий номер слова, використовується для управління порядком слова в грі.
    };



    std::vector<std::string> words;
    std::vector<WordText> wordTexts;
    sf::Font font;
    HUD& hud;
    float speed;
    float timeSinceLastSpawn;
    float spawnInterval = 2.0f;
    float speedMultiplier;
    sf::RenderWindow& window;
    int wordOrder;

    void loadWordsFromFile(const std::string &basicString);
};