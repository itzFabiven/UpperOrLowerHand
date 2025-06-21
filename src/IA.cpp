// IA.cpp
// Implementación de la lógica de la IA, incluyendo el algoritmo Minimax.
#include "IA.h"
#include <algorithm>
#include <set>
#include <iostream>

// Función auxiliar (no de la clase) para obtener las cartas que aún no han salido.
std::vector<Carta> obtenerCartasDisponibles(const std::list<Carta>& descartadas, const std::vector<Carta>& manoIA) {
    // Se crea un mazo doble completo de referencia.
    std::vector<Carta> todas;
    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    for (int i = 0; i < 2; ++i) {
        for (const auto& p : palos) {
            for (const auto& v : valores) {
                todas.emplace_back(p, v.first, v.second);
            }
        }
    }

    // Se usan sets para una búsqueda eficiente de las cartas ya vistas.
    std::set<std::pair<std::string, std::string>> cartasVistas;
    for (const auto& c : descartadas) {
        cartasVistas.insert({c.palo, c.valor});
    }
    for (const auto& c : manoIA) {
        cartasVistas.insert({c.palo, c.valor});
    }

    // Se filtran las cartas de la baraja completa para quedarse solo con las disponibles.
    std::vector<Carta> disponibles;
    for (const auto& c : todas) {
        if (cartasVistas.find({c.palo, c.valor}) == cartasVistas.end()) {
            disponibles.push_back(c);
        }
    }
    return disponibles;
}

// Función de evaluación: el "cerebro" del Minimax. Devuelve un puntaje para una jugada.
int IA::evaluarEstado(int sumaIA, int sumaJugador, const std::string& prediccion, int apuesta) {
    int score = 0;

    // Lógica principal: ¿la IA ganaría con esta predicción?
    bool iaGana = (prediccion == "mayor" && sumaIA > sumaJugador) ||
                  (prediccion == "menor" && sumaIA < sumaJugador);
    
    bool iaPierde = (prediccion == "mayor" && sumaIA < sumaJugador) ||
                     (prediccion == "menor" && sumaIA > sumaJugador);

    if (iaGana) {
        score += apuesta * 2; // Ganar es bueno.
    } else if (iaPierde) {
        score -= apuesta * 2; // Perder es malo.
    } else { // Empate
        score -= apuesta; // Empatar no es ideal, se penaliza ligeramente.
    }
    return score;
}

// Algoritmo Minimax con poda Alpha-Beta.
int IA::minimax(int profundidad, bool esMax, int sumaIA, int sumaJugador,
                const std::string& prediccionIA, int apuestaIA,
                int alpha, int beta,
                const std::vector<Carta>& disponibles) {

    // Condición base de la recursión: si llegamos al final de la profundidad, evaluamos el estado.
    if (profundidad == 0 || disponibles.size() < 2) {
        return evaluarEstado(sumaIA, sumaJugador, prediccionIA, apuestaIA);
    }

    // Turno del Maximizador (la IA)
    if (esMax) {
        int mejorValor = -100000;
        // Simula todas las posibles manos que podría tener el jugador.
        for (size_t i = 0; i < disponibles.size(); ++i) {
            for (size_t j = i + 1; j < disponibles.size(); ++j) {
                int nuevaSumaJugador = disponibles[i].puntaje + disponibles[j].puntaje;
                int valor = minimax(profundidad - 1, false, sumaIA, nuevaSumaJugador,
                                    prediccionIA, apuestaIA, alpha, beta, disponibles);
                mejorValor = std::max(mejorValor, valor);
                alpha = std::max(alpha, mejorValor);

                // Poda Alfa-Beta: si el minimizador ya tiene una opción mejor (beta) que la que estamos
                // explorando (alpha), no tiene sentido seguir por esta rama.
                if (beta <= alpha) {
                    break;
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return mejorValor;
    } else { // Turno del Minimizador (el Jugador)
        int mejorValor = 100000;
        // La simulación del turno del jugador es más simple, asumimos que siempre
        // buscará el peor escenario para la IA.
        // (En una implementación más compleja, simularíamos también la predicción del jugador).
        int valor = evaluarEstado(sumaIA, sumaJugador, prediccionIA, apuestaIA);
        mejorValor = std::min(mejorValor, valor);
        beta = std::min(beta, mejorValor);

        return mejorValor;
    }
}


// Método principal para tomar la decisión.
std::pair<std::string, int> IA::tomarDecision(int sumaIA, int puntosIA,
                                               const std::list<Carta>& cartasDescartadas,
                                               const std::vector<Carta>& manoIA) {
    std::string mejorPrediccion = "mayor";
    int mejorApuesta = 1;
    int mejorValor = -100000;

    std::vector<std::string> predicciones = {"mayor", "menor"};
    std::vector<int> apuestas = {1, 2, 3};

    std::vector<Carta> disponibles = obtenerCartasDisponibles(cartasDescartadas, manoIA);

    // Reglas heurísticas y atajos para casos obvios.
    if (sumaIA >= 25) return {"mayor", std::min(3, puntosIA)};
    if (sumaIA <= 6)  return {"menor", std::min(3, puntosIA)};

    // Itera sobre todas las jugadas posibles (combinación de predicción y apuesta).
    for (const auto& pred : predicciones) {
        for (int apu : apuestas) {
            if (apu > puntosIA) continue; // No puede apostar más de lo que tiene.

            // Ejecuta Minimax para evaluar qué tan buena es esta jugada.
            // La profundidad 1 es suficiente para este juego (simula la mano del oponente).
            int resultado = minimax(1, true, sumaIA, 0, pred, apu, -100000, 100000, disponibles);

            // Si el resultado de esta jugada es mejor que el mejor encontrado hasta ahora, lo guarda.
            if (resultado > mejorValor) {
                mejorValor = resultado;
                mejorPrediccion = pred;
                mejorApuesta = apu;
            }
        }
    }

    return {mejorPrediccion, mejorApuesta};
}
