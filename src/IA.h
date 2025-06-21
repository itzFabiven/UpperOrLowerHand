// IA.h
// Define la lógica de la Inteligencia Artificial del oponente.
// Es una clase puramente estática, lo que significa que no se crean objetos de tipo IA.
// Sus métodos se usan como utilidades para calcular la mejor jugada.
#pragma once

#include "Carta.h"
#include <list>
#include <string>
#include <utility>
#include <vector>

class IA {
public:
    /**
     * @brief Método principal que decide la predicción y apuesta de la IA.
     * @param sumaIA Suma de puntos de la mano actual de la IA.
     * @param puntosIA Puntos totales actuales de la IA.
     * @param cartasDescartadas Una lista de todas las cartas que ya han salido del juego.
     * @param manoIA La mano actual de la IA.
     * @return Un par (pair) que contiene la predicción ("mayor" o "menor") y la apuesta (1, 2 o 3).
     */
    static std::pair<std::string, int> tomarDecision(
        int sumaIA,
        int puntosIA,
        const std::list<Carta>& cartasDescartadas,
        const std::vector<Carta>& manoIA
    );

private:
    /**
     * @brief Función de evaluación para el algoritmo Minimax. Determina qué tan bueno es un estado del juego para la IA.
     * @param sumaIA Suma de la mano de la IA en una simulación.
     * @param sumaJugador Suma de la mano del jugador en una simulación.
     * @param prediccion La predicción que la IA está evaluando.
     * @param apuesta La apuesta que la IA está evaluando.
     * @return Un puntaje numérico. Un valor alto es favorable para la IA, un valor bajo es desfavorable.
     */
    static int evaluarEstado(
        int sumaIA,
        int sumaJugador,
        const std::string& prediccion,
        int apuesta
    );

    /**
     * @brief Implementación del algoritmo Minimax con poda Alpha-Beta.
     * Simula jugadas futuras para encontrar la mejor decisión posible.
     * @param profundidad Cuántos turnos hacia el futuro simular.
     * @param esMax True si es el turno de la IA (quiere maximizar el puntaje), false si es el turno del jugador (quiere minimizarlo).
     * @param sumaIA Suma actual de la mano de la IA.
     * @param sumaJugador Suma actual de la mano del jugador.
     * @param prediccionIA Predicción de la IA que se está simulando.
     * @param apuestaIA Apuesta de la IA que se está simulando.
     * @param alpha Mejor valor para el maximizador encontrado hasta ahora.
     * @param beta Peor valor para el minimizador encontrado hasta ahora.
     * @param disponibles Cartas que aún quedan en el mazo para simular las manos del oponente.
     * @return El puntaje de la mejor jugada encontrada en la simulación.
     */
    static int minimax(
        int profundidad,
        bool esMax,
        int sumaIA, int sumaJugador,
        const std::string& prediccionIA,
        int apuestaIA,
        int alpha, int beta,
        const std::vector<Carta>& disponibles
    );
};

