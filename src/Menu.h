// src/Menu.h
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"

#define MAX_NUMBER_OF_ITEMS 5 // <<< CORREGIDO: de 4 a 5

class Menu {
public:
    Menu(float width, float height, const sf::Font& font);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, GameState& currentState);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font gameFont;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    float windowWidth;
    float windowHeight;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif // MENU_H