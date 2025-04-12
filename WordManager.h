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
    void handleInput(sf::Event& event);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void reset();

    void setSpeedMultiplier(float multiplier);
    void setSpawnInterval(float interval);


    void setFont(const sf::Font& font);
    float getSpeedMultiplier() const;


private:
    struct WordText {
        sf::Text text;
        int order;
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