// src/GameScreen.h
// Define la clase para la pantalla principal del juego.
// Es responsable de toda la lógica de presentación y de la interacción
// del usuario durante la partida (apuestas, predicciones, etc.).
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <sstream>
#include "GameState.h"
#include "Juego.h"
#include "Carta.h"

class GameScreen {
public:
    /**
     * @brief Constructor de la pantalla de juego.
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     * @param font Fuente global para los textos.
     * @param playerName Nombre del jugador humano.
     */
    GameScreen(float width, float height, const sf::Font& font, const std::string& playerName);

    /**
     * @brief Gestiona los eventos del usuario (clics, teclado) para esta pantalla.
     * @param window Referencia a la ventana principal para mapear coordenadas del ratón.
     * @param event El evento actual a procesar.
     * @param currentState El estado actual del juego, que puede ser modificado.
     */
    void handleEvent(sf::RenderWindow& window, const sf::Event& event, GameState& currentState);

    /**
     * @brief Actualiza la lógica de la pantalla que depende del tiempo (ej. animaciones).
     * @param deltaTime El tiempo transcurrido desde el último fotograma.
     */
    void update(float deltaTime);

    /**
     * @brief Dibuja todos los elementos de la pantalla de juego en la ventana.
     * @param window La ventana donde se va a dibujar.
     */
    void draw(sf::RenderWindow& window);

private:
    // --- Recursos Visuales y de UI ---
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font gameFont;
    float windowWidth;
    float windowHeight;

    // --- Lógica del Juego ---
    Juego gameLogic; // Instancia del motor del juego que contiene las reglas

    // --- Recursos de Cartas ---
    sf::Texture cardBackTexture; // Textura para el dorso de la carta
    std::map<std::string, sf::Texture> cardFaceTextures; // Mapa para almacenar las texturas de las caras de las cartas

    // --- Estado de la Interfaz (UI) y del Juego ---
    bool cardsDealt;     // ¿Se han repartido las cartas en esta ronda?
    bool roundEnded;     // ¿Ha terminado la ronda?
    bool gameFinished;   // ¿Ha terminado la partida por completo?
    bool showResult;     // ¿Deben mostrarse las cartas de la IA y los resultados de la ronda?
    bool bettingPhase;     // ¿Está el jugador en la fase de apuesta?
    bool declarationPhase; // ¿Está el jugador en la fase de declaración?

    // --- Elementos de Texto de la UI ---
    sf::Text playerPointsText, opponentPointsText, roundText;
    sf::Text gameMessageText;   // Para mensajes centrales ("Elige tu apuesta", resultado de ronda, etc.)
    sf::Text iaDecisionText, iaBetText;
    sf::Text playerScoreText, opponentScoreText;

    // --- Elementos de Botones de la UI ---
    sf::RectangleShape bet1ButtonShape, bet2ButtonShape, bet3ButtonShape;
    sf::Text bet1ButtonText, bet2ButtonText, bet3ButtonText;
    sf::RectangleShape higherButtonShape, lowerButtonShape;
    sf::Text higherButtonText, lowerButtonText;
    sf::RectangleShape continueButtonShape;
    sf::Text continueButtonText;
    
    // --- Variables de Animación ---
    sf::Clock animationClock;
    float animationDuration;
    bool animatingOpponentCard;

    // --- Funciones Auxiliares Privadas ---
    void setupButton(sf::RectangleShape& shape, sf::Text& text, float x, float y, const std::string& label);
    void updateUITexts();   // Actualiza los textos de puntos y ronda
    void startNewRoundUI(); // Resetea la UI para una nueva ronda
    void loadCardTextures();
    void drawCarta(sf::RenderWindow& window, const Carta& card, float x, float y, bool faceUp) const;
    std::string getCardTextureFileName(const Carta& card) const;
};

#endif // GAMESCREEN_H