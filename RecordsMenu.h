#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsMenu.h"
#include <vector>
#include <string>

class RecordsMenu {
public:
    RecordsMenu(float width, float height, const sf::Font& font); // Конструктор ініціалізує меню записів, задаючи розміри вікна та шрифт
    void draw(sf::RenderWindow& window); // Відповідає за відмалювання усіх елементів меню на екрані.
    void loadRecords(const std::string& filename); // Завантажує записи з файла, ім'я якого передається як аргумент.
    sf::FloatRect getBackButtonBounds() const;
    bool hasReachedRecordLimit(const std::string& filename, int limit); // Перевіряє, чи кількість записів у файлі досягла заданого ліміту. Це важливо для контролювання максимальної кількості збережених записів.
    void saveRecord(const std::string& name, int score, const std::string& speedMode, const std::string& fontName); // Зберігає новий запис у файл. Запис містить ім'я гравця, його бал, швидкість гри та використаний шрифт.
    bool recordsChanged; // Логічна змінна, яка вказує, чи були змінені записи (додані або видалені



private:
    const sf::Font& font;
    std::vector<sf::Text> records;
    sf::Text backButton;
    sf::Text noRecordsText;
};

