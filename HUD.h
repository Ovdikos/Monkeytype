
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD {
public:
    HUD(const sf::Font& font);
    void setInputText(const std::string& input);
    std::string getInputText() const;
    void setCorrectCount(int count);
    void setIncorrectCount(int count);
    int getIncorrectCount() const;
    int getCorrectCount() const;
    void reset();
    void render(sf::RenderWindow& window);

private:
    sf::Text inputText;
    sf::Text correctText;
    sf::Text incorrectText;
    sf::RectangleShape inputBox;
    sf::RectangleShape correctCountBox;
    sf::Texture bubbleTexture;
    std::vector<sf::Sprite> bubbles;
    int correctCount;
    int incorrectCount;
};
