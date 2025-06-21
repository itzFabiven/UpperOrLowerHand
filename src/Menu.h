// src/Menu.h
// Define la clase para la pantalla del Menú Principal.
// Gestiona la navegación entre las opciones del menú.
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"

#define MAX_NUMBER_OF_ITEMS 5 // Número de opciones en el menú

class Menu {
public:
    /**
     * @brief Constructor de la clase Menu.
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     * @param font Fuente a utilizar para los textos.
     */
    Menu(float width, float height, const sf::Font& font);

    /**
     * @brief Dibuja todos los elementos del menú en la ventana.
     * @param window La ventana donde se va a dibujar.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Gestiona los eventos del usuario (teclado) para esta pantalla.
     * @param event El evento actual a procesar.
     * @param currentState El estado actual del juego, que puede ser modificado por la selección del usuario.
     */
    void handleEvent(const sf::Event& event, GameState& currentState);

    /**
     * @brief Mueve la selección del menú hacia arriba.
     */
    void moveUp();

    /**
     * @brief Mueve la selección del menú hacia abajo.
     */
    void moveDown();

    /**
     * @brief Obtiene el índice del ítem seleccionado actualmente.
     * @return El índice del ítem (0 para JUGAR, 1 para REGLAS, etc.).
     */
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex; // Índice de la opción seleccionada actualmente (0, 1, 2, 3, 4)
    sf::Font gameFont;     // Copia de la fuente principal del juego
    sf::Text menu[MAX_NUMBER_OF_ITEMS]; // Array de textos para las opciones del menú
    float windowWidth;
    float windowHeight;

    // Elementos visuales del fondo
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif // MENU_H