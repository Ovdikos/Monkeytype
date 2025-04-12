#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("help/font.ttf")) {
    }

    std::string menuItems[4] = {"Play", "Settings", "Records", "Exit"};
    for (int i = 0; i < 4; ++i) {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(menuItems[i]);
        menu[i].setPosition(sf::Vector2f(width / 2 - menu[i].getGlobalBounds().width / 2, height / (4 + 1) * (i + 1)));
        menu[i].setOutlineThickness(3);
        menu[i].setOutlineColor(sf::Color::Black);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 4; ++i) {
        window.draw(menu[i]);
    }
}

int Menu::getPressedItem(int mouseX, int mouseY) {
    for (int i = 0; i < 4; ++i) {
        if (menu[i].getGlobalBounds().contains(mouseX, mouseY)) {
            return i;
        }
    }
    return -1;
}
