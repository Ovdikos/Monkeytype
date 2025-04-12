#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsMenu.h"
#include <vector>
#include <string>

class RecordsMenu {
public:
    RecordsMenu(float width, float height, const sf::Font& font);
    void draw(sf::RenderWindow& window);
    void loadRecords(const std::string& filename);
    sf::FloatRect getBackButtonBounds() const;
    bool hasReachedRecordLimit(const std::string& filename, int limit);
    void saveRecord(const std::string& name, int score, const std::string& speedMode, const std::string& fontName);
    bool recordsChanged;



private:
    const sf::Font& font;
    std::vector<sf::Text> records;
    sf::Text backButton;
    sf::Text noRecordsText;
};

