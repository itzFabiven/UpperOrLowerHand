// src/RulesScreen.cpp
#include "RulesScreen.h"
#include <iostream>
#include <SFML/System/String.hpp>

RulesScreen::RulesScreen(float width, float height, const sf::Font& font)
    : gameFont(font), windowWidth(width), windowHeight(height)
{
    // --- 1. Cargar Recursos ---
    if (!backgroundTexture.loadFromFile("images/fondo_menu.jpg")) {
        std::cerr << "Error cargando fondo_menu.jpg" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        width / backgroundSprite.getLocalBounds().width,
        height / backgroundSprite.getLocalBounds().height
    );

    std::vector<std::string> cardsToLoad = {
        "2_Diamante", "3_Diamante", "4_Diamante", "5_Diamante", "6_Diamante", "7_Diamante", "8_Diamante", "9_Diamante", "10_Diamante",
        "J_Diamante", "Q_Diamante", "K_Diamante", "As_Diamante", "2_Corazon", "K_Trebol"
    };
    for(const auto& cardName : cardsToLoad) {
        loadCardTexture(cardName);
    }
    
    // --- 2. Configurar Textos y Sprites (Layout Reajustado) ---
    setupText(titleText, "Reglas: Valor de las Cartas", 70, {width / 2, 80.f});
    titleText.setFillColor(sf::Color::Yellow);

    // --- Sección de Valores de Cartas ---
    float cardY = 220.f; // <<< MODIFICADO: Un poco más abajo
    float valueTextY = cardY + 280.f; 
    int valueFontSize = 28;         

    // Grupo de cartas 2-10
    float numberCardScale = 1.5f;   
    float numberGroupStartX = width / 2.f - 880.f; // <<< MODIFICADO: Más a la izquierda
    float numberCardSpacing = 65.f;               
    for(int i = 0; i < 9; ++i) { // 2 a 10 de diamantes
        sf::Sprite sprite;
        sprite.setTexture(cardTextures[cardsToLoad[i]]);
        sprite.setScale(numberCardScale, numberCardScale);
        sprite.setPosition(numberGroupStartX + i * numberCardSpacing, cardY);
        diamondSprites.push_back(sprite);
    }
    setupText(numberCardsValueText, "Valor: 2 al 10", valueFontSize, {numberGroupStartX + (8 * numberCardSpacing / 2.f), valueTextY});

    // Grupo de figuras individuales
    float faceCardScale = 2.5f;     
    float faceCardStartX = numberGroupStartX + 9 * numberCardSpacing + 200.f; // <<< MODIFICADO: Más a la izquierda y más junto
    float faceCardSpacing = 280.f; // <<< MODIFICADO: Más juntas

    // Jack
    sf::Sprite jackSprite(cardTextures["J_Diamante"]);
    jackSprite.setScale(faceCardScale, faceCardScale);
    jackSprite.setPosition(faceCardStartX, cardY);
    diamondSprites.push_back(jackSprite);
    setupText(jackValueText, "Valor: 11", valueFontSize, {jackSprite.getPosition().x + jackSprite.getGlobalBounds().width / 2.f, valueTextY});

    // Queen
    sf::Sprite queenSprite(cardTextures["Q_Diamante"]);
    queenSprite.setScale(faceCardScale, faceCardScale);
    queenSprite.setPosition(faceCardStartX + faceCardSpacing, cardY);
    diamondSprites.push_back(queenSprite);
    setupText(queenValueText, "Valor: 12", valueFontSize, {queenSprite.getPosition().x + queenSprite.getGlobalBounds().width / 2.f, valueTextY});
    
    // King
    sf::Sprite kingSprite(cardTextures["K_Diamante"]);
    kingSprite.setScale(faceCardScale, faceCardScale);
    kingSprite.setPosition(faceCardStartX + 2 * faceCardSpacing, cardY);
    diamondSprites.push_back(kingSprite);
    setupText(kingValueText, "Valor: 13", valueFontSize, {kingSprite.getPosition().x + kingSprite.getGlobalBounds().width / 2.f, valueTextY});

    // Ace
    sf::Sprite aceSprite(cardTextures["As_Diamante"]);
    aceSprite.setScale(faceCardScale, faceCardScale);
    aceSprite.setPosition(faceCardStartX + 3 * faceCardSpacing, cardY);
    diamondSprites.push_back(aceSprite);
    setupText(aceValueText, "Valor: 14", valueFontSize, {aceSprite.getPosition().x + aceSprite.getGlobalBounds().width / 2.f, valueTextY});

    // --- Sección de Ejemplo (Layout anterior restaurado) ---
    setupText(explanationText, "La suma de tu mano depende del valor de la carta.", 35, {width / 2, 600.f});
    
    setupText(exampleTitleText, "Por Ejemplo:", 35, {width / 2, 680.f});
    exampleTitleText.setStyle(sf::Text::Bold);

    exampleCard1.setTexture(cardTextures["2_Corazon"]);
    exampleCard1.setScale(1.8f, 1.8f); 
    exampleCard1.setOrigin(exampleCard1.getLocalBounds().width / 2.f, 0);
    exampleCard1.setPosition(width / 2 - 120, 730.f);

    exampleCard2.setTexture(cardTextures["K_Trebol"]);
    exampleCard2.setScale(1.8f, 1.8f);
    exampleCard2.setOrigin(exampleCard2.getLocalBounds().width / 2.f, 0);
    exampleCard2.setPosition(width / 2 + 120, 730.f);

    std::string exText = "... suman 15 (2 + 13), es decir, tu mano vale 15.";
    // <<< MODIFICADO: Posición justo encima del botón VOLVER, un poco más arriba que antes
    setupText(exampleText, exText, 30, {width / 2, height - 200});

    // --- Botón de Volver ---
    backButtonShape.setSize({250, 80});
    backButtonShape.setFillColor(sf::Color(70, 70, 70, 200));
    backButtonShape.setOutlineColor(sf::Color::White);
    backButtonShape.setOutlineThickness(2);
    backButtonShape.setOrigin(backButtonShape.getLocalBounds().width / 2, backButtonShape.getLocalBounds().height / 2);
    backButtonShape.setPosition(width / 2, height - 80);
    setupText(backButtonText, "VOLVER", 40, {width / 2, height - 80});
}

void RulesScreen::handleEvent(const sf::Event& event, GameState& currentState) {
    if (event.type == sf::Event::Closed) {
        currentState = EXIT;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentState = MENU;
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (backButtonShape.getGlobalBounds().contains(mousePos)) {
                currentState = MENU;
            }
        }
    }
}

void RulesScreen::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(titleText);

    // Dibuja la fila de cartas de valor
    for(const auto& sprite : diamondSprites) {
        window.draw(sprite);
    }
    
    // Dibuja los textos de valor
    window.draw(numberCardsValueText);
    window.draw(jackValueText);
    window.draw(queenValueText);
    window.draw(kingValueText);
    window.draw(aceValueText);
    
    // Dibuja la sección de ejemplo
    window.draw(explanationText);
    window.draw(exampleTitleText);
    window.draw(exampleCard1);
    window.draw(exampleCard2);
    window.draw(exampleText);
    
    // Dibuja el botón
    window.draw(backButtonShape);
    window.draw(backButtonText);
}

void RulesScreen::setupText(sf::Text& text, const std::string& content, int size, sf::Vector2f position) {
    text.setString(sf::String::fromUtf8(content.begin(), content.end()));
    text.setFont(gameFont);
    text.setCharacterSize(size);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f,
                   textBounds.top + textBounds.height / 2.f);
    text.setPosition(position);
}

void RulesScreen::loadCardTexture(const std::string& cardName) {
    if (cardTextures.find(cardName) == cardTextures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile("cards/" + cardName + ".png")) {
            std::cerr << "Error cargando textura para reglas: " << cardName << ".png" << std::endl;
        } else {
            cardTextures[cardName] = texture;
        }
    }
}