#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    int getPressedItem(int mouseX, int mouseY);



private:
    sf::Font font;
    sf::Text menu[4];
};


