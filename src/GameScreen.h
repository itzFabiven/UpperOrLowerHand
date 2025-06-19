// src/GameScreen.h
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
    GameScreen(float width, float height, const sf::Font& font, const std::string& playerName);

    void handleEvent(sf::RenderWindow& window, const sf::Event& event, GameState& currentState);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font gameFont;
    float windowWidth;
    float windowHeight;

    Juego gameLogic;

    sf::Texture cardBackTexture;
    std::map<std::string, sf::Texture> cardFaceTextures;

    std::string getCardTextureFileName(const Carta& card) const;
    void loadCardTextures();
    void drawCarta(sf::RenderWindow& window, const Carta& card, float x, float y, bool faceUp) const;

    bool cardsDealt;
    bool roundEnded;
    bool gameFinished;
    bool showResult;

    sf::Text playerPointsText;
    sf::Text opponentPointsText;
    sf::Text roundText;
    sf::Text gameMessageText;
    sf::Text iaDecisionText;
    sf::Text iaBetText;
    sf::Text playerScoreText;
    sf::Text opponentScoreText; // <<< NUEVO: Texto para la suma de la IA

    sf::RectangleShape bet1ButtonShape;
    sf::Text bet1ButtonText;
    sf::RectangleShape bet2ButtonShape;
    sf::Text bet2ButtonText;
    sf::RectangleShape bet3ButtonShape;
    sf::Text bet3ButtonText;

    bool bettingPhase;
    bool declarationPhase;
    sf::RectangleShape higherButtonShape;
    sf::Text higherButtonText;
    sf::RectangleShape lowerButtonShape;
    sf::Text lowerButtonText;

    sf::RectangleShape continueButtonShape;
    sf::Text continueButtonText;

    int currentBetAmount;
    std::string playerPrediction;

    std::string roundResultMessage;
    std::string gameEndMessage;

    sf::Clock animationClock;
    float animationDuration;
    sf::Vector2f opponentCardAnimationStartPos;
    sf::Vector2f opponentCardAnimationEndPos;
    bool animatingOpponentCard;

    void setupButton(sf::RectangleShape& shape, sf::Text& text, float x, float y, const std::string& label);
    void updateUITexts();
    void startNewRoundUI();
};

#endif // GAMESCREEN_H