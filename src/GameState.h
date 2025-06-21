// src/GameState.h
// Define los diferentes estados o "pantallas" posibles de la aplicación.
// Esto permite al bucle principal en main.cpp saber qué lógica y qué pantalla dibujar.

#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GameState {
    MENU,       // Estado para el menú principal
    GAME,       // Estado para la pantalla de juego principal
    RULES,      // Estado para la pantalla de reglas
    OPTIONS,    // Estado para una futura pantalla de opciones
    CREDITS,    // Estado para la pantalla de créditos
    EXIT        // Estado especial para cerrar la aplicación
};

#endif // GAMESTATE_H