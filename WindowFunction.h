#pragma once
#include <SFML/Graphics.hpp>
#include "HUD.h"
#include "WordManager.h"
#include "Menu.h"
#include "SettingsMenu.h"
#include "RecordsMenu.h"

class Window {
public:
    Window(const std::string& wordsFile);
    void run();

    enum class Screen { Menu, Game, Settings, Records, GameOver };

private:
    sf::RenderWindow window;
    HUD hud;
    WordManager wordManager;


    sf::Texture menuBackgroundTexture;
    sf::Texture gameBackgroundTexture;
    sf::Texture gameOverBackgroundTexture;
    sf::Texture settingsBackgroundTexture;
    sf::Texture recordsBackgroundTexture;
    sf::Texture happyrecordsBackgroundTexture;
    sf::Sprite background;


    sf::Font font;
    sf::Text gameOverText;
    sf::Text playAgainText;
    sf::Text saveResultsButton;
    sf::Text menuButton;
    sf::Text inputNamePromptText;
    sf::Text playerNameText;


    int currentScreen;
    Menu menu;
    SettingsMenu settingsMenu;
    RecordsMenu recordsMenu;
    std::string playerName;
    bool enteringName;
    sf::Cursor defaultCursor;
    sf::Cursor handCursor;
    bool recordLimitReached;
    sf::Text recordLimitReachedText;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();


};
