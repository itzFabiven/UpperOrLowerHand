// src/RulesScreen.h
#ifndef RULESSCREEN_H
#define RULESSCREEN_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "GameState.h"

class RulesScreen {
public:
    RulesScreen(float width, float height, const sf::Font& font);
    void handleEvent(const sf::Event& event, GameState& currentState);
    void draw(sf::RenderWindow& window);

private:
    sf::Font gameFont;
    float windowWidth;
    float windowHeight;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Text titleText;
    sf::Text explanationText;
    sf::Text exampleTitleText;
    sf::Text exampleText;
    sf::Text backButtonText;
    sf::RectangleShape backButtonShape;
    
    // Almacén de texturas para no cargar repetidamente
    std::map<std::string, sf::Texture> cardTextures;
    
    // Sprites para todas las cartas de ejemplo
    std::vector<sf::Sprite> diamondSprites; // Para la fila de diamantes
    sf::Sprite exampleCard1; // 2 de Corazones
    sf::Sprite exampleCard2; // K de Tréboles

    // Textos para los valores de las cartas
    sf::Text numberCardsValueText;
    sf::Text jackValueText;
    sf::Text queenValueText;
    sf::Text kingValueText;
    sf::Text aceValueText;

    void setupText(sf::Text& text, const std::string& content, int size, sf::Vector2f position);
    void loadCardTexture(const std::string& cardName);
};

#endif // RULESSCREEN_H