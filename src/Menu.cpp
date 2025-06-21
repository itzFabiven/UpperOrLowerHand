// src/Menu.cpp
// Implementación de la pantalla del Menú Principal.
// Se encarga de inicializar los elementos visuales del menú y de gestionar la navegación.
#include "Menu.h"
#include <iostream>

// Constructor del Menú: configura todos los elementos visuales.
Menu::Menu(float width, float height, const sf::Font& font)
    : gameFont(font), windowWidth(width), windowHeight(height), selectedItemIndex(0)
{
    // --- Carga de Recursos Visuales ---
    if (!backgroundTexture.loadFromFile("images/fondo_menu.jpg")) {
        std::cerr << "Error cargando la imagen de fondo del menu: images/fondo_menu.jpg" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        // Escala la imagen de fondo para que ocupe toda la ventana.
        backgroundSprite.setScale(
            static_cast<float>(windowWidth) / backgroundTexture.getSize().x,
            static_cast<float>(windowHeight) / backgroundTexture.getSize().y
        );
    }

    // --- Configuración de las Opciones del Menú ---
    // Se definen posiciones para distribuir los 5 ítems en la pantalla.
    float initialY = windowHeight / 2.f - 240;
    float stepY = 120;

    // JUGAR (Ítem 0)
    menu[0].setFont(gameFont);
    menu[0].setCharacterSize(80);
    menu[0].setFillColor(sf::Color::Red); // La primera opción empieza seleccionada
    menu[0].setString("JUGAR");
    menu[0].setOrigin(menu[0].getLocalBounds().left + menu[0].getLocalBounds().width / 2.f, menu[0].getLocalBounds().top + menu[0].getLocalBounds().height / 2.f);
    menu[0].setPosition(windowWidth / 2.f, initialY);

    // REGLAS (Ítem 1)
    menu[1].setFont(gameFont);
    menu[1].setCharacterSize(80);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("REGLAS");
    menu[1].setOrigin(menu[1].getLocalBounds().left + menu[1].getLocalBounds().width / 2.f, menu[1].getLocalBounds().top + menu[1].getLocalBounds().height / 2.f);
    menu[1].setPosition(windowWidth / 2.f, initialY + stepY);

    // OPCIONES (Ítem 2)
    menu[2].setFont(gameFont);
    menu[2].setCharacterSize(80);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("OPCIONES");
    menu[2].setOrigin(menu[2].getLocalBounds().left + menu[2].getLocalBounds().width / 2.f, menu[2].getLocalBounds().top + menu[2].getLocalBounds().height / 2.f);
    menu[2].setPosition(windowWidth / 2.f, initialY + 2 * stepY);

    // CREDITOS (Ítem 3)
    menu[3].setFont(gameFont);
    menu[3].setCharacterSize(80);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("CREDITOS");
    menu[3].setOrigin(menu[3].getLocalBounds().left + menu[3].getLocalBounds().width / 2.f, menu[3].getLocalBounds().top + menu[3].getLocalBounds().height / 2.f);
    menu[3].setPosition(windowWidth / 2.f, initialY + 3 * stepY);

    // SALIR (Ítem 4)
    menu[4].setFont(gameFont);
    menu[4].setCharacterSize(80);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("SALIR");
    menu[4].setOrigin(menu[4].getLocalBounds().left + menu[4].getLocalBounds().width / 2.f, menu[4].getLocalBounds().top + menu[4].getLocalBounds().height / 2.f);
    menu[4].setPosition(windowWidth / 2.f, initialY + 4 * stepY);
}

// Dibuja todos los elementos del menú en la ventana pasada como referencia.
void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

// Gestiona la entrada del usuario (teclado) para el menú.
void Menu::handleEvent(const sf::Event& event, GameState& currentState) {
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            case sf::Keyboard::Return: // Tecla Enter
                // Cambia el estado del juego según la opción seleccionada.
                switch (getPressedItem()) {
                    case 0: currentState = GAME; break;
                    case 1: currentState = RULES; break;
                    case 2: currentState = OPTIONS; break;
                    case 3: currentState = CREDITS; break;
                    case 4: currentState = EXIT; break;
                }
                break;
            default:
                break;
        }
    }
    // Si el usuario cierra la ventana, se cambia al estado de salida.
    else if (event.type == sf::Event::Closed) {
        currentState = EXIT;
    }
}

// Lógica para mover la selección hacia arriba en el menú.
void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White); // El ítem actual vuelve a ser blanco
        selectedItemIndex--; // Se cambia el índice
        menu[selectedItemIndex].setFillColor(sf::Color::Red);   // El nuevo ítem se pone rojo
    }
}

// Lógica para mover la selección hacia abajo en el menú.
void Menu::moveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}