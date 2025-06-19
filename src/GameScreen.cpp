// src/GameScreen.cpp
#include "GameScreen.h"
#include <iostream>
#include <string>

// Constructor de GameScreen
GameScreen::GameScreen(float width, float height, const sf::Font& font, const std::string& playerName)
    : gameFont(font), windowWidth(width), windowHeight(height),
      gameLogic(playerName),
      cardsDealt(false), roundEnded(false), gameFinished(false), showResult(false),
      currentBetAmount(0), bettingPhase(true), declarationPhase(false),
      animatingOpponentCard(false), animationDuration(0.5f)
{
    if (!backgroundTexture.loadFromFile("images/mesa_juego.jpg")) {
        std::cerr << "Error cargando la imagen de fondo: images/mesa_juego.jpg" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        float scaleX = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    loadCardTextures();
    if (!cardBackTexture.loadFromFile("cards/dorso_carta.png")) {
        std::cerr << "Error cargando la textura del dorso: cards/dorso_carta.png" << std::endl;
    }

    // Configurar textos de UI
    playerPointsText.setFont(gameFont);
    playerPointsText.setCharacterSize(40);
    playerPointsText.setFillColor(sf::Color::White);
    playerPointsText.setPosition(50, windowHeight - 100);

    opponentPointsText.setFont(gameFont);
    opponentPointsText.setCharacterSize(40);
    opponentPointsText.setFillColor(sf::Color::White);
    opponentPointsText.setPosition(50, 50);

    roundText.setFont(gameFont);
    roundText.setCharacterSize(40);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition(windowWidth - 300, 50);

    gameMessageText.setFont(gameFont);
    gameMessageText.setCharacterSize(60);
    gameMessageText.setFillColor(sf::Color::Yellow);

    iaDecisionText.setFont(gameFont);
    iaDecisionText.setCharacterSize(30);
    iaDecisionText.setFillColor(sf::Color::Cyan);

    iaBetText.setFont(gameFont);
    iaBetText.setCharacterSize(30);
    iaBetText.setFillColor(sf::Color::Cyan);

    playerScoreText.setFont(gameFont);
    playerScoreText.setCharacterSize(40);
    playerScoreText.setFillColor(sf::Color::White);
    playerScoreText.setPosition(50, windowHeight - 150);

    opponentScoreText.setFont(gameFont);
    opponentScoreText.setCharacterSize(40);
    opponentScoreText.setFillColor(sf::Color::White);
    opponentScoreText.setPosition(50, 100);

    // Configurar botones
    setupButton(bet1ButtonShape, bet1ButtonText, windowWidth / 2.f - 200, windowHeight - 200, "APOSTAR 1");
    setupButton(bet2ButtonShape, bet2ButtonText, windowWidth / 2.f, windowHeight - 200, "APOSTAR 2");
    setupButton(bet3ButtonShape, bet3ButtonText, windowWidth / 2.f + 200, windowHeight - 200, "APOSTAR 3");
    setupButton(higherButtonShape, higherButtonText, windowWidth / 2.f - 150, windowHeight - 200, "MAYOR");
    setupButton(lowerButtonShape, lowerButtonText, windowWidth / 2.f + 150, windowHeight - 200, "MENOR");
    setupButton(continueButtonShape, continueButtonText, windowWidth / 2.f, windowHeight / 2.f + 200, "CONTINUAR");

    gameLogic.iniciarNuevaRonda();
    cardsDealt = true;
    updateUITexts();
}

void GameScreen::setupButton(sf::RectangleShape& shape, sf::Text& text, float x, float y, const std::string& label) {
    shape.setSize(sf::Vector2f(180, 70));
    shape.setFillColor(sf::Color(70, 70, 70, 200));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
    shape.setPosition(x, y);

    text.setFont(gameFont);
    text.setString(label);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.f,
                   text.getLocalBounds().top + text.getLocalBounds().height / 2.f);
    text.setPosition(x, y);
}

void GameScreen::loadCardTextures() {
    std::vector<std::string> palos = {"Corazon", "Picas", "Diamante", "Trebol"};
    std::vector<std::string> valores = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    for (const auto& palo : palos) {
        for (const auto& valor : valores) {
            std::string filename = "cards/" + valor + "_" + palo + ".png";
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                std::cerr << "Error cargando textura: " << filename << std::endl;
            } else {
                cardFaceTextures[valor + "_" + palo] = texture;
            }
        }
    }
}

std::string GameScreen::getCardTextureFileName(const Carta& card) const {
    std::string rankStr;
    if (card.valor == "A") rankStr = "As";
    else if (card.valor == "J") rankStr = "J";
    else if (card.valor == "Q") rankStr = "Q";
    else if (card.valor == "K") rankStr = "K";
    else rankStr = card.valor;

    std::string suitStr;
    if (card.palo == "♥") suitStr = "Corazon";
    else if (card.palo == "♠") suitStr = "Picas";
    else if (card.palo == "♦") suitStr = "Diamante";
    else if (card.palo == "♣") suitStr = "Trebol";

    return rankStr + "_" + suitStr;
}

void GameScreen::drawCarta(sf::RenderWindow& window, const Carta& card, float x, float y, bool faceUp) const {
    sf::Sprite cardSprite;
    if (faceUp) {
        std::string textureKey = getCardTextureFileName(card);
        if (cardFaceTextures.count(textureKey)) {
            cardSprite.setTexture(cardFaceTextures.at(textureKey));
        } else {
            std::cerr << "ERROR: Textura no encontrada para la carta: " << card.valor << " de " << card.palo << " (Clave: " << textureKey << ")\n";
            cardSprite.setTexture(cardBackTexture);
        }
    } else {
        cardSprite.setTexture(cardBackTexture);
    }
    cardSprite.setPosition(x, y);
    cardSprite.setScale(1.6f, 1.6f);
    window.draw(cardSprite);
}

void GameScreen::handleEvent(sf::RenderWindow& window, const sf::Event& event, GameState& currentState) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        if (gameFinished) {
            currentState = MENU;
            gameLogic.reiniciarJuego();
            startNewRoundUI();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if (gameFinished) {
                if (continueButtonShape.getGlobalBounds().contains(mousePos)) {
                    currentState = MENU;
                    gameLogic.reiniciarJuego();
                    startNewRoundUI();
                }
            } else if (bettingPhase) {
                if (bet1ButtonShape.getGlobalBounds().contains(mousePos)) {
                    gameLogic.setApuestaJugador(1);
                    bettingPhase = false; declarationPhase = true; updateUITexts();
                } else if (bet2ButtonShape.getGlobalBounds().contains(mousePos)) {
                    gameLogic.setApuestaJugador(2);
                    bettingPhase = false; declarationPhase = true; updateUITexts();
                } else if (bet3ButtonShape.getGlobalBounds().contains(mousePos)) {
                    gameLogic.setApuestaJugador(3);
                    bettingPhase = false; declarationPhase = true; updateUITexts();
                }
            } else if (declarationPhase) {
                if (higherButtonShape.getGlobalBounds().contains(mousePos) || lowerButtonShape.getGlobalBounds().contains(mousePos)) {
                    gameLogic.setPrediccionJugador(higherButtonShape.getGlobalBounds().contains(mousePos) ? "mayor" : "menor");
                    declarationPhase = false;
                    roundEnded = true;
                    showResult = true;
                    gameLogic.resolverRonda();
                    updateUITexts();
                    gameFinished = gameLogic.isPartidaFinalizada();
                }
            } else if (roundEnded && showResult) {
                if (continueButtonShape.getGlobalBounds().contains(mousePos)) {
                    if (gameFinished) {
                        currentState = MENU;
                        gameLogic.reiniciarJuego();
                        startNewRoundUI();
                    } else {
                        gameLogic.iniciarNuevaRonda();
                        startNewRoundUI();
                    }
                }
            }
        }
    }
}

void GameScreen::update(float deltaTime) {
    if (animatingOpponentCard) {
        // Lógica de animación
    }
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(playerPointsText);
    window.draw(opponentPointsText);
    window.draw(roundText);

    gameMessageText.setOrigin(gameMessageText.getLocalBounds().left + gameMessageText.getLocalBounds().width / 2.f,
                              gameMessageText.getLocalBounds().top + gameMessageText.getLocalBounds().height / 2.f);
    gameMessageText.setPosition(windowWidth / 2.f, windowHeight / 2.f);

    if (gameFinished) {
        gameMessageText.setString(gameLogic.getMensajeFinalPartida());
        window.draw(gameMessageText);
        window.draw(continueButtonShape);
        window.draw(continueButtonText);
    } else {
        // --- DIBUJO DE CARTAS Y SUMAS ---
        const auto& playerHand = gameLogic.obtenerManoJugador();
        if (playerHand.size() == 2) {
            float playerCardX = windowWidth / 2.f - 250;
            float playerCardY = windowHeight - 480;
            drawCarta(window, playerHand[0], playerCardX, playerCardY, true);
            drawCarta(window, playerHand[1], playerCardX + 400, playerCardY, true);

            playerScoreText.setString("Suma: " + std::to_string(gameLogic.obtenerManoJugadorSuma()));
            window.draw(playerScoreText);
        }

        const auto& opponentHand = gameLogic.obtenerManoIA();
        if (opponentHand.size() == 2) {
            float opponentCardX = windowWidth / 2.f - 250;
            float opponentCardY = 320;
            drawCarta(window, opponentHand[0], opponentCardX, opponentCardY, showResult);
            drawCarta(window, opponentHand[1], opponentCardX + 400, opponentCardY, showResult);
        }
        
        // --- DIBUJO DE INFO DE LA IA (Solo al final de la ronda) ---
        if (showResult) {
            opponentScoreText.setString("Suma IA: " + std::to_string(gameLogic.obtenerManoIASuma()));
            window.draw(opponentScoreText);

            iaDecisionText.setString("IA predijo: " + gameLogic.getPrediccionIA());
            iaDecisionText.setOrigin(iaDecisionText.getLocalBounds().left + iaDecisionText.getLocalBounds().width / 2.f,
                                     iaDecisionText.getLocalBounds().top + iaDecisionText.getLocalBounds().height / 2.f);
            iaDecisionText.setPosition(windowWidth / 2.f, 180);
            window.draw(iaDecisionText);

            iaBetText.setString("IA aposto: " + std::to_string(gameLogic.getApuestaIA()));
            iaBetText.setOrigin(iaBetText.getLocalBounds().left + iaBetText.getLocalBounds().width / 2.f,
                                iaBetText.getLocalBounds().top + iaBetText.getLocalBounds().height / 2.f);
            iaBetText.setPosition(windowWidth / 2.f, 210);
            window.draw(iaBetText);
        }

        // --- DIBUJO DE BOTONES Y MENSAJES DE FASE ---
        if (bettingPhase) {
            gameMessageText.setString("Elige tu apuesta:");
            window.draw(bet1ButtonShape); window.draw(bet1ButtonText);
            window.draw(bet2ButtonShape); window.draw(bet2ButtonText);
            window.draw(bet3ButtonShape); window.draw(bet3ButtonText);
        } else if (declarationPhase) {
            // <<< CORREGIDO: Usando el método explícito sf::String::fromUtf8
            std::string msg = "¿Tu mano es Mayor o Menor?";
            gameMessageText.setString(sf::String::fromUtf8(msg.begin(), msg.end()));
            window.draw(higherButtonShape); window.draw(higherButtonText);
            window.draw(lowerButtonShape); window.draw(lowerButtonText);
        } else if (roundEnded) {
            gameMessageText.setString(gameLogic.getMensajeRonda());
            window.draw(continueButtonShape);
            window.draw(continueButtonText);
        }
        window.draw(gameMessageText);
    }
}

void GameScreen::updateUITexts() {
    playerPointsText.setString("Tus puntos: " + std::to_string(gameLogic.getPuntosJugador()));
    opponentPointsText.setString("Puntos IA: " + std::to_string(gameLogic.getPuntosIA()));
    roundText.setString("Ronda: " + std::to_string(gameLogic.getRondaActual()));
}

void GameScreen::startNewRoundUI() {
    cardsDealt = true;
    roundEnded = false;
    showResult = false;
    bettingPhase = true;
    declarationPhase = false;
    currentBetAmount = 0;
    playerPrediction = "";
    updateUITexts();
}