// src/main.cpp
// Punto de entrada principal de la aplicación.
// Se encarga de crear la ventana, gestionar los estados del juego (Menú, Juego, Reglas)
// y contiene el bucle principal que actualiza y dibuja cada fotograma.

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Menu.h"
#include "GameScreen.h"
#include "RulesScreen.h"
#include "GameState.h"

int main() {
    // --- Configuración Inicial de la Ventana ---
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Juego de Cartas: Mayor o Menor");
    window.setFramerateLimit(60); // Limitar a 60 FPS para un rendimiento estable

    // --- Carga de Recursos Globales (Fuentes y Música) ---
    sf::Font font;
    if (!font.loadFromFile("fonts/times.ttf")) {
        std::cerr << "Error cargando la fuente: fonts/times.ttf" << std::endl;
        return -1;
    }

    // Creación de los objetos para cada pantalla del juego
    std::string playerName = "Jugador";
    Menu menu(windowWidth, windowHeight, font);
    GameScreen gameScreen(windowWidth, windowHeight, font, playerName);
    RulesScreen rulesScreen(windowWidth, windowHeight, font);

    // Carga y configuración de la música de fondo
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

    // --- Variables de Estado del Juego ---
    GameState currentState = MENU; // El juego siempre empieza en el menú principal

    // Estado para controlar la música y evitar reiniciarla en cada fotograma
    enum MusicState { MUSIC_NONE, MUSIC_MENU, MUSIC_GAME };
    MusicState currentMusicState = MUSIC_NONE;

    sf::Clock clock; // Reloj para controlar el tiempo delta (para animaciones futuras)

    // --- Bucle Principal del Juego ---
    // Este bucle se ejecuta continuamente mientras la ventana esté abierta.
    while (window.isOpen()) {
        sf::Event event;
        // Bucle de gestión de eventos (input del usuario)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Se delega el manejo de eventos a la pantalla activa
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
        
        // Lógica para controlar qué música debe sonar según el estado del juego
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

        // --- Ciclo de Dibujado ---
        window.clear(); // Limpia la pantalla del fotograma anterior

        float deltaTime = clock.restart().asSeconds();

        // Se dibuja la pantalla que corresponda al estado actual
        switch (currentState) {
            case MENU:
                menu.draw(window);
                break;
            case GAME:
                gameScreen.update(deltaTime); // Actualiza la lógica de la pantalla
                gameScreen.draw(window);      // Dibuja la pantalla
                break;
            case RULES:
                rulesScreen.draw(window);
                break;
            // Pantallas simples para Opciones y Créditos
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

        window.display(); // Muestra en pantalla todo lo que se ha dibujado
    }

    return 0;
}