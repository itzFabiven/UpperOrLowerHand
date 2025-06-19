// src/Menu.cpp
#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, const sf::Font& font)
    : gameFont(font), windowWidth(width), windowHeight(height), selectedItemIndex(0)
{
    if (!backgroundTexture.loadFromFile("images/fondo_menu.jpg")) {
        std::cerr << "Error cargando la imagen de fondo del menu: images/fondo_menu.jpg" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        float scaleX = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    // <<< CORREGIDO: Ajuste de posiciones para 5 ítems
    float initialY = windowHeight / 2.f - 240;
    float stepY = 120;

    // JUGAR
    menu[0].setFont(gameFont);
    menu[0].setCharacterSize(80);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("JUGAR");
    menu[0].setOrigin(menu[0].getLocalBounds().left + menu[0].getLocalBounds().width / 2.f, menu[0].getLocalBounds().top + menu[0].getLocalBounds().height / 2.f);
    menu[0].setPosition(windowWidth / 2.f, initialY);

    // <<< NUEVO: Botón REGLAS
    menu[1].setFont(gameFont);
    menu[1].setCharacterSize(80);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("REGLAS");
    menu[1].setOrigin(menu[1].getLocalBounds().left + menu[1].getLocalBounds().width / 2.f, menu[1].getLocalBounds().top + menu[1].getLocalBounds().height / 2.f);
    menu[1].setPosition(windowWidth / 2.f, initialY + stepY);

    // OPCIONES (ahora es el ítem 2)
    menu[2].setFont(gameFont);
    menu[2].setCharacterSize(80);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("OPCIONES");
    menu[2].setOrigin(menu[2].getLocalBounds().left + menu[2].getLocalBounds().width / 2.f, menu[2].getLocalBounds().top + menu[2].getLocalBounds().height / 2.f);
    menu[2].setPosition(windowWidth / 2.f, initialY + 2 * stepY);

    // CREDITOS (ahora es el ítem 3)
    menu[3].setFont(gameFont);
    menu[3].setCharacterSize(80);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("CREDITOS");
    menu[3].setOrigin(menu[3].getLocalBounds().left + menu[3].getLocalBounds().width / 2.f, menu[3].getLocalBounds().top + menu[3].getLocalBounds().height / 2.f);
    menu[3].setPosition(windowWidth / 2.f, initialY + 3 * stepY);

    // SALIR (ahora es el ítem 4)
    menu[4].setFont(gameFont);
    menu[4].setCharacterSize(80);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("SALIR");
    menu[4].setOrigin(menu[4].getLocalBounds().left + menu[4].getLocalBounds().width / 2.f, menu[4].getLocalBounds().top + menu[4].getLocalBounds().height / 2.f);
    menu[4].setPosition(windowWidth / 2.f, initialY + 4 * stepY);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::handleEvent(const sf::Event& event, GameState& currentState) {
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        } else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        } else if (event.key.code == sf::Keyboard::Return) {
            // <<< CORREGIDO: Se añade el caso para REGLAS y se actualizan los demás
            switch (getPressedItem()) {
                case 0: // JUGAR
                    currentState = GAME;
                    break;
                case 1: // REGLAS
                    currentState = RULES;
                    break;
                case 2: // OPCIONES
                    currentState = OPTIONS;
                    break;
                case 3: // CREDITOS
                    currentState = CREDITS;
                    break;
                case 4: // SALIR
                    currentState = EXIT;
                    break;
            }
        }
    }
    else if (event.type == sf::Event::Closed) {
        currentState = EXIT;
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}