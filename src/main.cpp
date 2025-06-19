// src/main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Menu.h"
#include "GameScreen.h"
#include "RulesScreen.h" // <<< NUEVO
#include "GameState.h"

int main() {
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Juego de Cartas: Mayor o Menor");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("fonts/times.ttf")) {
        std::cerr << "Error cargando la fuente: fonts/times.ttf" << std::endl;
        return -1;
    }

    std::string playerName = "Jugador";

    Menu menu(windowWidth, windowHeight, font);
    GameScreen gameScreen(windowWidth, windowHeight, font, playerName);
    RulesScreen rulesScreen(windowWidth, windowHeight, font); // <<< NUEVO

    sf::Music menuMusic;
    if (!menuMusic.openFromFile("audio/menu_song.ogg")) {
        std::cerr << "Error al cargar audio/menu_song.ogg" << std::endl;
    }
    menuMusic.setLoop(true);
    menuMusic.setVolume(50);

    sf::Music gameMusic;
    if (!gameMusic.openFromFile("audio/play_song.ogg")) {
        std::cerr << "Error al cargar audio/play_song.ogg" << std::endl;
    }
    gameMusic.setLoop(true);
    gameMusic.setVolume(50);

    enum MusicState { MUSIC_NONE, MUSIC_MENU, MUSIC_GAME };
    MusicState currentMusicState = MUSIC_NONE;

    GameState currentState = MENU;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // <<< CORREGIDO: Se añade el caso para RULES
            switch (currentState) {
                case MENU:
                    menu.handleEvent(event, currentState);
                    break;
                case GAME:
                    gameScreen.handleEvent(window, event, currentState);
                    break;
                case RULES: 
                    rulesScreen.handleEvent(event, currentState);
                    break;
                case OPTIONS:
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        currentState = MENU;
                    }
                    break;
                case CREDITS:
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        currentState = MENU;
                    }
                    break;
                case EXIT:
                    window.close();
                    break;
            }
        }
        
        // <<< CORREGIDO: Se añade RULES al control de música
        switch (currentState) {
            case MENU:
            case RULES:
            case OPTIONS:
            case CREDITS:
                if (currentMusicState != MUSIC_MENU) {
                    gameMusic.stop();
                    menuMusic.play();
                    currentMusicState = MUSIC_MENU;
                }
                break;
            case GAME:
                if (currentMusicState != MUSIC_GAME) {
                    menuMusic.stop();
                    gameMusic.play();
                    currentMusicState = MUSIC_GAME;
                }
                break;
            case EXIT:
                menuMusic.stop();
                gameMusic.stop();
                break;
        }

        window.clear();
        float deltaTime = clock.restart().asSeconds();

        // <<< CORREGIDO: Se añade el caso para dibujar la pantalla de reglas
        switch (currentState) {
            case MENU:
                menu.draw(window);
                break;
            case GAME:
                gameScreen.update(deltaTime);
                gameScreen.draw(window);
                break;
            case RULES:
                rulesScreen.draw(window);
                break;
            case OPTIONS: {
                std::string msg = "Opciones\n(Presiona ESC para volver)";
                sf::Text optionsText(sf::String::fromUtf8(msg.begin(), msg.end()), font, 50);
                optionsText.setOrigin(optionsText.getLocalBounds().left + optionsText.getLocalBounds().width / 2.f, optionsText.getLocalBounds().top + optionsText.getLocalBounds().height / 2.f);
                optionsText.setPosition(windowWidth / 2.f, windowHeight / 2.f);
                window.draw(optionsText);
                break;
            }
            case CREDITS: {
                std::string msg = "Desarrollado por: Fabian Zaballos\n(Presiona ESC para volver)";
                sf::Text creditsText(sf::String::fromUtf8(msg.begin(), msg.end()), font, 50);
                creditsText.setOrigin(creditsText.getLocalBounds().left + creditsText.getLocalBounds().width / 2.f, creditsText.getLocalBounds().top + creditsText.getLocalBounds().height / 2.f);
                creditsText.setPosition(windowWidth / 2.f, windowHeight / 2.f);
                window.draw(creditsText);
                break;
            }
            case EXIT:
                break;
        }

        window.display();
    }

    return 0;
}