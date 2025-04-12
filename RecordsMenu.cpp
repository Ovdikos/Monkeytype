#include "RecordsMenu.h"
#include "fmt/core.h"
#include <fstream>
#include <sstream>
#include <iostream>

RecordsMenu::RecordsMenu(float width, float height, const sf::Font& font)
        : font(font) {
    backButton.setFont(font);
    backButton.setString("Back");
    backButton.setCharacterSize(50);
    backButton.setFillColor(sf::Color::White);
    backButton.setPosition(width / 2 - backButton.getGlobalBounds().width / 2, height - 100);


    noRecordsText.setFont(font);
    noRecordsText.setCharacterSize(50);
    noRecordsText.setFillColor(sf::Color::White);
    noRecordsText.setOrigin(noRecordsText.getLocalBounds().width / 2, noRecordsText.getLocalBounds().height / 2);
    noRecordsText.setPosition((width / 2 - noRecordsText.getGlobalBounds().width / 2) - 420, height * 0.15);
}

// Відмальовує текст записів або текст "немає записів", якщо список порожній, а також кнопку повернення.
void RecordsMenu::draw(sf::RenderWindow& window) {
    if (records.empty()) {
        window.draw(noRecordsText);
    } else {
        for (const auto& record : records) {
            window.draw(record);
        }
    }
    window.draw(backButton);
}


void RecordsMenu::loadRecords(const std::string& filename) {
    records.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open records file" << std::endl;
        return;
    }

    std::string line;
    float yOffset = 100.0f;
    while (std::getline(file, line)) {
        sf::Text recordText;
        recordText.setFont(font);
        recordText.setCharacterSize(30);
        recordText.setFillColor(sf::Color::White);

        std::cerr << "Read line: " << line << std::endl;

        // Setting the position of each record text
        recordText.setPosition(100.0f, yOffset);
        recordText.setString(line);
        records.push_back(recordText);

        yOffset += 50.0f;
    }

    file.close();


    if (records.empty()) {
        noRecordsText.setString("There are no any records, let's start playing!");
    } else {
        noRecordsText.setString("");
    }
}

sf::FloatRect RecordsMenu::getBackButtonBounds() const {
    return backButton.getGlobalBounds();
}



bool RecordsMenu::hasReachedRecordLimit(const std::string& filename, int limit) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open records file" << std::endl;
        return false; // Assuming no records if file can't be opened
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        count++;
    }

    return count >= limit;
}

void RecordsMenu::saveRecord(const std::string& name, int score, const std::string& speedMode, const std::string& fontName) {
    std::ofstream file("help/records.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open records file\n";
        return;
    }
    file << name << " " << score << " " << speedMode << " " << fontName << "\n";
    file.close();

    bool recordsChanged = true;
}




