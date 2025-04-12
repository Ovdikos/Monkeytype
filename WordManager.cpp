#include "WordManager.h"
#include <fstream>
#include <iostream>

WordManager::WordManager(const std::string &wordsFile, HUD &hud, sf::RenderWindow &window)
        : hud(hud), speed(100.0f), timeSinceLastSpawn(0.0f), spawnInterval(2.0f), speedMultiplier(1.0f), window(window), wordOrder(0) {
    if (!font.loadFromFile("help/font.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    loadWordsFromFile(wordsFile);
}

void WordManager::loadWordsFromFile(const std::string& wordsFile) {
    std::ifstream file(wordsFile);
    if (!file) {
        std::cerr << "Failed to open words file\n";
        return;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
}

void WordManager::update(float deltaTime) {
    timeSinceLastSpawn += deltaTime;

    //  Перевіряє, чи пора вже генерувати нове слово
    if (timeSinceLastSpawn > spawnInterval / speedMultiplier) {
        if (!words.empty()) {
            int randomIndex = rand() % words.size();
            sf::Text text(words[randomIndex], font, 30);
            text.setFillColor(sf::Color::White);
            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(2);
            text.setPosition(-100.0f, rand() % (window.getSize().y - 200));

            wordTexts.push_back({text, wordOrder++});
        }
        timeSinceLastSpawn = 0;
    }

    for (auto& wordText : wordTexts) {
        wordText.text.move(speed * deltaTime * speedMultiplier, 0);


        if (wordText.text.getPosition().x > window.getSize().x / 2) {
            wordText.text.setFillColor(sf::Color::Yellow);
        }
        if (wordText.text.getPosition().x > 3 * window.getSize().x / 4) {
            wordText.text.setFillColor(sf::Color::Red);
        }

        if (wordText.text.getPosition().x > window.getSize().x) {
            hud.setIncorrectCount(hud.getIncorrectCount() + 1);
            wordText.text.setPosition(-100.0f, rand() % (window.getSize().y - 200));
            wordText.text.setFillColor(sf::Color::White);
        }
    }
}

void WordManager::render(sf::RenderWindow& window) {
    for (const auto& wordText : wordTexts) {
        window.draw(wordText.text);
    }
}

void WordManager::reset() {
    wordTexts.clear();
    timeSinceLastSpawn = 0.0f;
    wordOrder = 0;
}

void WordManager::handleInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        char inputChar = static_cast<char>(event.text.unicode);

        if (inputChar == '\b') {
            std::string currentInput = hud.getInputText();
            if (!currentInput.empty()) {
                currentInput.pop_back();
                hud.setInputText(currentInput);
            }

        } else if (inputChar == '\r' || inputChar == '\n') {
            std::string currentInput = hud.getInputText();
            bool correct = false;
            for (auto it = wordTexts.begin(); it != wordTexts.end();) {
                if (it->text.getString() == currentInput) {
                    it->text.setFillColor(sf::Color::Blue);
                    it = wordTexts.erase(it);
                    hud.setCorrectCount(hud.getCorrectCount() + 1);
                    correct = true;
                    break;
                } else {
                    ++it;
                }
            }
            if (!correct) {
                hud.setIncorrectCount(hud.getIncorrectCount() + 1);
            }
            hud.setInputText("");
        } else if (std::isalpha(inputChar)) {
            hud.setInputText(hud.getInputText() + inputChar);
        }
    }
}

void WordManager::setSpeedMultiplier(float multiplier) {
    if (multiplier <= 0) {
        speedMultiplier = 0;
    } else {
        speedMultiplier = multiplier;
    }
}

float WordManager::getSpeedMultiplier() const {
    return speedMultiplier;
}

void WordManager::setSpawnInterval(float interval) {
    spawnInterval = interval;

}


void WordManager::setFont(const sf::Font& newFont) {
    font = newFont;  // Оновлюємо внутрішній шрифт
    for (auto& wordText : wordTexts) {
        wordText.text.setFont(font);
    }
}
