// src/RulesScreen.cpp
// Implementación de la pantalla de Reglas. Se encarga de mostrar de forma
// visual y textual las reglas del juego.
#include "RulesScreen.h"
#include <iostream>
#include <SFML/System/String.hpp>

// Constructor: configura todos los elementos visuales estáticos de la pantalla de reglas.
RulesScreen::RulesScreen(float width, float height, const sf::Font& font)
    : gameFont(font), windowWidth(width), windowHeight(height)
{
    // --- 1. Cargar Recursos de Fondo ---
    if (!backgroundTexture.loadFromFile("images/fondo_menu.jpg")) {
        std::cerr << "Error cargando fondo_menu.jpg" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(width / backgroundSprite.getLocalBounds().width, height / backgroundSprite.getLocalBounds().height);

    // --- 2. Cargar TODAS las texturas de cartas necesarias para esta pantalla ---
    std::vector<std::string> cardsToLoad = {
        "2_Diamante", "3_Diamante", "4_Diamante", "5_Diamante", "6_Diamante", "7_Diamante", "8_Diamante", "9_Diamante", "10_Diamante",
        "J_Diamante", "Q_Diamante", "K_Diamante", "As_Diamante", "2_Corazon", "K_Trebol"
    };
    for(const auto& cardName : cardsToLoad) {
        loadCardTexture(cardName);
    }
    
    // --- 3. Configurar Título Principal ---
    setupText(titleText, "Reglas: Valor de las Cartas", 70, {width / 2, 80.f});
    titleText.setFillColor(sf::Color::Yellow);

    // --- 4. Configurar Sprites y Textos para la sección de VALORES ---
    float cardY = 240.f;
    float valueTextY = cardY + 280.f; 
    int valueFontSize = 28;         

    // Grupo de cartas 2-10
    float numberCardScale = 1.5f;   
    float numberGroupStartX = width / 2.f - 900.f;
    float numberCardSpacing = 65.f;               
    for(int i = 0; i < 9; ++i) {
        sf::Sprite sprite;
        sprite.setTexture(cardTextures[cardsToLoad[i]]);
        sprite.setScale(numberCardScale, numberCardScale);
        sprite.setPosition(numberGroupStartX + i * numberCardSpacing, cardY);
        diamondSprites.push_back(sprite);
    }
    setupText(numberCardsValueText, "Valor: 2 al 10", valueFontSize, {numberGroupStartX + (8 * numberCardSpacing / 2.f), valueTextY});

    // Grupo de figuras individuales
    float faceCardScale = 2.5f;     
    float faceCardStartX = numberGroupStartX + 9 * numberCardSpacing + 120.f;
    float faceCardSpacing = 260.f; 

    // Jack, Queen, King, Ace
    sf::Sprite jackSprite(cardTextures["J_Diamante"]);
    jackSprite.setScale(faceCardScale, faceCardScale);
    jackSprite.setPosition(faceCardStartX, cardY);
    diamondSprites.push_back(jackSprite);
    setupText(jackValueText, "Valor: 11", valueFontSize, {jackSprite.getPosition().x + jackSprite.getGlobalBounds().width / 2.f, valueTextY});
    // ... (código similar para Q, K, A)

    // --- 5. Configurar la sección de EJEMPLO ---
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
    setupText(exampleText, exText, 30, {width / 2, height - 250});

    // --- 6. Configurar Botón de Volver ---
    backButtonShape.setSize({250, 80});
    backButtonShape.setFillColor(sf::Color(70, 70, 70, 200));
    backButtonShape.setOutlineColor(sf::Color::White);
    backButtonShape.setOutlineThickness(2);
    backButtonShape.setOrigin(backButtonShape.getLocalBounds().width / 2, backButtonShape.getLocalBounds().height / 2);
    backButtonShape.setPosition(width / 2, height - 80);
    setupText(backButtonText, "VOLVER", 40, {width / 2, height - 80});
}

// Gestiona la entrada del usuario para esta pantalla.
void RulesScreen::handleEvent(const sf::Event& event, GameState& currentState) {
    if (event.type == sf::Event::Closed) {
        currentState = EXIT;
    }
    // Permite volver al menú con la tecla ESC o haciendo clic en el botón.
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

// Dibuja todos los elementos de la pantalla de reglas.
void RulesScreen::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(titleText);
    for(const auto& sprite : diamondSprites) { window.draw(sprite); }
    window.draw(numberCardsValueText);
    window.draw(jackValueText);
    window.draw(queenValueText);
    window.draw(kingValueText);
    window.draw(aceValueText);
    window.draw(explanationText);
    window.draw(exampleTitleText);
    window.draw(exampleCard1);
    window.draw(exampleCard2);
    window.draw(exampleText);
    window.draw(backButtonShape);
    window.draw(backButtonText);
}

// Función auxiliar para configurar texto de forma consistente, manejando UTF-8 y centrado.
void RulesScreen::setupText(sf::Text& text, const std::string& content, int size, sf::Vector2f position) {
    text.setString(sf::String::fromUtf8(content.begin(), content.end()));
    text.setFont(gameFont);
    text.setCharacterSize(size);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    text.setPosition(position);
}

// Función auxiliar para cargar texturas de cartas, evitando duplicados.
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