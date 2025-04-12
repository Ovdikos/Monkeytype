#include "HUD.h"
#include <iostream>

HUD::HUD(const sf::Font& font) {
    std::cout << "Initializing HUD..." << std::endl;


    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(960, 1000); // Центруємо текст


    correctText.setFont(font);
    correctText.setCharacterSize(30);
    correctText.setFillColor(sf::Color::Black);
    correctText.setString("Correct: 0");
    correctText.setPosition(60,1010);


    inputBox.setFillColor(sf::Color(255, 165, 0, 200)); // Orange
    inputBox.setOutlineColor(sf::Color::Blue);
    inputBox.setOutlineThickness(5);
    inputBox.setSize(sf::Vector2f(500, 60));
    inputBox.setPosition(710, 985);


    correctCountBox.setFillColor(sf::Color(144, 238, 144, 200));
    correctCountBox.setOutlineColor(sf::Color::Red);
    correctCountBox.setOutlineThickness(5);
    correctCountBox.setSize(sf::Vector2f(200, 50));
    correctCountBox.setPosition(50, 1000);


    if (!bubbleTexture.loadFromFile("help/buble.png")) {
        std::cerr << "Failed to load bubble texture" << std::endl;
    }


    for (int i = 0; i < 5; ++i) {
        sf::Sprite bubble(bubbleTexture);
        bubble.setPosition(1520 + i * 60, 1000);
        bubbles.push_back(bubble);
    }
}

void HUD::setInputText(const std::string &input) {
    inputText.setString(input);
    inputText.setOrigin(inputText.getLocalBounds().width / 2, inputText.getLocalBounds().height / 2); // Центрування тексту
}

std::string HUD::getInputText() const {
    return inputText.getString();
}

void HUD::setCorrectCount(int count) {
    correctCount = count;
    correctText.setString("Correct: " + std::to_string(count));
}

void HUD::setIncorrectCount(int count) {
    incorrectCount = count;
    incorrectText.setString("Incorrect: " + std::to_string(count));
    for (int i = 0; i < bubbles.size(); ++i) {
        if (i < incorrectCount) {
            bubbles[i].setColor(sf::Color::Transparent);
        } else {
            bubbles[i].setColor(sf::Color::White);
        }
    }
}

int HUD::getIncorrectCount() const {
    return incorrectCount;
}

int HUD::getCorrectCount() const {
    return correctCount;
}

void HUD::reset() {
    correctCount = 0;
    incorrectCount = 0;
    inputText.setString("");
    correctText.setString("Correct: 0");
    incorrectText.setString("Incorrect: 0");
    for (auto& bubble : bubbles) {
        bubble.setColor(sf::Color::White);
    }
}


void HUD::render(sf::RenderWindow& window) {
    window.draw(inputBox);
    window.draw(correctCountBox);
    window.draw(inputText);
    window.draw(correctText);
    window.draw(incorrectText);
    for (const auto& bubble : bubbles) {
        window.draw(bubble);
    }
}
