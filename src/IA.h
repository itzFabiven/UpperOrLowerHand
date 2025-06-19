// IA.h
#pragma once

#include "Carta.h"
#include <list>    // Para la lista de cartas descartadas
#include <string>  // Para las predicciones
#include <utility> // Para std::pair
#include <vector>  // Para la mano y cartas disponibles

// La clase IA es puramente estática, contiene la lógica de decisión
// de la inteligencia artificial del oponente. No tiene estado interno
// como un jugador (mano, puntos), sino que opera sobre datos pasados.
class IA {
public:
    // Método principal para que la IA decida su predicción y apuesta.
    // Toma como entrada el estado actual relevante (mano de la IA, sus puntos,
    // cartas ya vistas, etc.)
    static std::pair<std::string, int> tomarDecision(
        int sumaIA,                             // Suma de puntos de la mano actual de la IA
        int puntosIA,                           // Puntos actuales de la IA
        const std::list<Carta>& cartasDescartadas, // Cartas ya fuera de juego
        const std::vector<Carta>& manoIA        // Cartas que la IA tiene en su mano
    );

private:
    // Función de evaluación usada por el algoritmo Minimax para determinar el valor de un estado.
    static int evaluarEstado(
        int sumaIA,           // Suma de la mano de la IA en la simulación
        int sumaJugador,      // Suma de la mano del Jugador en la simulación
        const std::string& prediccion, // Predicción de la IA en la simulación
        int apuesta            // Apuesta de la IA en la simulación
    );

    // Implementación del algoritmo Minimax con poda Alpha-Beta.
    // Simula jugadas futuras para encontrar la mejor decisión.
    static int minimax(
        int profundidad,               // Profundidad de búsqueda del árbol de juego
        bool esMax,                    // True si es turno de maximizar (IA), false si es turno de minimizar (Jugador)
        int sumaIA, int sumaJugador,   // Sumas de las manos en la simulación actual
        const std::string& prediccionIA, // Predicción de la IA para la simulación
        int apuestaIA,                 // Apuesta de la IA para la simulación
        int puntosIA, int puntosJugador, // Puntos de los jugadores en la simulación (pueden no usarse en cada nodo)
        int alpha, int beta,           // Parámetros de poda Alpha-Beta
        const std::vector<Carta>& disponibles // Cartas disponibles para futuras jugadas simuladas
    );
};

