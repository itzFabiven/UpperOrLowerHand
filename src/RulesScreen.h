// src/RulesScreen.h
// Define la clase para la pantalla de Reglas.
// Muestra información estática y visual sobre cómo jugar al juego.
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
    // --- Recursos Visuales y de UI ---
    sf::Font gameFont;
    float windowWidth;
    float windowHeight;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // --- Elementos de Texto ---
    sf::Text titleText;
    sf::Text explanationText;
    sf::Text exampleTitleText;
    sf::Text exampleText;
    sf::Text backButtonText;
    sf::RectangleShape backButtonShape;
    sf::Text numberCardsValueText, jackValueText, queenValueText, kingValueText, aceValueText;
    
    // --- Sprites y Texturas para Ejemplos Visuales ---
    std::map<std::string, sf::Texture> cardTextures; // Almacén de texturas para evitar cargas repetidas
    std::vector<sf::Sprite> diamondSprites;         // Sprites para la fila de diamantes
    sf::Sprite exampleCard1, exampleCard2;

    // --- Funciones Auxiliares ---
    void setupText(sf::Text& text, const std::string& content, int size, sf::Vector2f position);
    void loadCardTexture(const std::string& cardName);
};

#endif // RULESSCREEN_H