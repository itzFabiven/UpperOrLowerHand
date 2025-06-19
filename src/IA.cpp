// IA.cpp
#include "IA.h"
#include <algorithm> // Para std::max, std::min, std::find_if
#include <cstdlib>   // Para funciones de C estándar (no utilizadas directamente para aleatoriedad aquí)
#include <ctime>     // Para std::time (no utilizada directamente aquí, pero útil para semillas)
#include <iostream>  // Para depuración si fuera necesario
#include <set>       // Para un manejo eficiente de las cartas descartadas

// Función auxiliar para generar la lista de cartas que aún no han sido vistas.
// No es miembro de IA, es una función global (enlace interno por estar en .cpp).
std::vector<Carta> obtenerCartasDisponibles(const std::list<Carta>& descartadas, const std::vector<Carta>& manoIA) {
    std::vector<Carta> todas; // Representa una doble baraja completa
    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    // Llenar 'todas' con dos barajas completas
    for (int i = 0; i < 2; ++i) {
        for (const auto& p : palos) {
            for (const auto& v : valores) {
                todas.emplace_back(p, v.first, v.second);
            }
        }
    }

    // Usar un set para las cartas vistas (manoIA + descartadas) para búsquedas rápidas
    std::set<std::pair<std::string, std::string>> cartasVistas;
    for (const auto& c : descartadas) {
        cartasVistas.insert({c.palo, c.valor});
    }
    for (const auto& c : manoIA) { // La mano de la IA también se considera "vista"
        cartasVistas.insert({c.palo, c.valor});
    }

    std::vector<Carta> disponibles;
    for (const auto& c : todas) {
        if (cartasVistas.find({c.palo, c.valor}) == cartasVistas.end()) {
            disponibles.push_back(c);
        }
    }
    return disponibles;
}


// Función de evaluación: Cuanto mayor el valor retornado, mejor para la IA.
// Es crucial para el Minimax.
int IA::evaluarEstado(int sumaIA, int sumaJugador, const std::string& prediccion, int apuesta) {
    int score = 0;

    // Lógica de evaluación basada en la predicción y el resultado potencial
    bool iaGana = (prediccion == "mayor" && sumaIA > sumaJugador) ||
                  (prediccion == "menor" && sumaIA < sumaJugador);

    bool iaPierde = (prediccion == "mayor" && sumaIA < sumaJugador) ||
                    (prediccion == "menor" && sumaIA > sumaJugador);

    if (iaGana) {
        score += apuesta * 2; // Gana el doble de la apuesta por acertar
    } else if (iaPierde) {
        score -= apuesta * 2; // Pierde el doble de la apuesta por fallar
    } else {
        // Empate, o sumas iguales
        score -= apuesta; // Consideramos que el empate es una pequeña pérdida o no ganancia
    }

    // Ajustes adicionales por la fuerza de la mano
    if (prediccion == "mayor" && sumaIA >= 20) score += 5; // Manos fuertes para mayor
    if (prediccion == "menor" && sumaIA <= 8) score += 5;  // Manos débiles para menor

    return score;
}

// Implementación del algoritmo Minimax con poda Alpha-Beta
int IA::minimax(int profundidad, bool esMax, int sumaIA, int sumaJugador,
                const std::string& prediccionIA, int apuestaIA,
                int puntosIA, int puntosJugador, // Estos puntos son de la simulación
                int alpha, int beta,
                const std::vector<Carta>& disponibles) {

    // Condición base: si la profundidad es 0, evalúa el estado actual.
    // También, si no hay suficientes cartas disponibles para completar una mano
    // en la simulación, se detiene.
    if (profundidad == 0) {
        return evaluarEstado(sumaIA, sumaJugador, prediccionIA, apuestaIA);
    }

    // Limitar la profundidad de búsqueda si hay muy pocas cartas disponibles
    // Esto evita simulaciones con manos incompletas
    if (disponibles.size() < 2) { // Necesita al menos 2 cartas para simular una mano del oponente
        return evaluarEstado(sumaIA, sumaJugador, prediccionIA, apuestaIA);
    }


    if (esMax) { // Turno de la IA (Maximizador)
        int mejorValor = -100000; // Un valor muy bajo
        // Simula las posibles manos que podría tener el jugador para cada par de cartas disponibles
        for (size_t i = 0; i < disponibles.size(); ++i) {
            for (size_t j = i + 1; j < disponibles.size(); ++j) {
                int nuevaSumaJugador = disponibles[i].puntaje + disponibles[j].puntaje;
                // Recursive call for the opponent's turn (minimizing)
                int valor = minimax(profundidad - 1, false, sumaIA, nuevaSumaJugador,
                                    prediccionIA, apuestaIA, puntosIA, puntosJugador, alpha, beta,
                                    disponibles); // Las disponibles no cambian en esta simulación simplificada

                mejorValor = std::max(mejorValor, valor);
                alpha = std::max(alpha, mejorValor);
                if (beta <= alpha) {
                    break; // Poda Beta
                }
            }
            if (beta <= alpha) {
                break; // Poda Beta exterior
            }
        }
        return mejorValor;
    } else { // Turno del Jugador (Minimizador)
        int mejorValor = 100000; // Un valor muy alto
        // El jugador también "elige" una predicción y apuesta para minimizar la ganancia de la IA.
        // Aquí la simulación es simplificada: asume que el jugador también juega óptimamente.
        for (size_t i = 0; i < disponibles.size(); ++i) {
            for (size_t j = i + 1; j < disponibles.size(); ++j) {
                int nuevaSumaIA = disponibles[i].puntaje + disponibles[j].puntaje; // Cartas restantes
                // Simula el peor escenario para la IA (mejor para el jugador)
                int valor = minimax(profundidad - 1, true, nuevaSumaIA, sumaJugador,
                                    prediccionIA, apuestaIA, puntosIA, puntosJugador, alpha, beta,
                                    disponibles); // Las disponibles no cambian en esta simulación simplificada

                mejorValor = std::min(mejorValor, valor);
                beta = std::min(beta, mejorValor);
                if (beta <= alpha) {
                    break; // Poda Alpha
                }
            }
            if (beta <= alpha) {
                break; // Poda Alpha exterior
            }
        }
        return mejorValor;
    }
}

// Método principal de la IA para tomar una decisión
std::pair<std::string, int> IA::tomarDecision(int sumaIA, int puntosIA,
                                               const std::list<Carta>& cartasDescartadas,
                                               const std::vector<Carta>& manoIA) {
    std::string mejorPrediccion = "mayor";
    int mejorApuesta = 1;
    int mejorValor = -100000; // Inicializar con un valor muy bajo

    std::vector<std::string> predicciones = {"mayor", "menor"};
    std::vector<int> apuestas = {1, 2, 3}; // Las posibles apuestas

    // Obtener las cartas que quedan en el mazo (no descartadas y no en la mano de la IA)
    std::vector<Carta> disponibles = obtenerCartasDisponibles(cartasDescartadas, manoIA);

    // Casos especiales para manos muy fuertes o muy débiles (optimización/regla del juego).
    // Estos son atajos que sobreescriben la lógica Minimax para casos obvios.
    if (sumaIA == 28) return {"mayor", std::min(3, puntosIA)}; // IA tiene la mano más alta posible (dos Ases)
    if (sumaIA == 4)  return {"menor", std::min(3, puntosIA)}; // IA tiene la mano más baja posible (dos Doses)

    // Si la mano de la IA es fuerte, podría apostar más y predecir "mayor"
    if (sumaIA >= 20 && sumaIA < 28) { // Ejemplo: K+Q (25), K+J (24), Q+J (23)
        // Asegurarse de que la apuesta no exceda los puntos disponibles
        int apuestaSugerida = std::min(3, puntosIA);
        // Si tiene al menos 20 y le quedan suficientes puntos, predice mayor y apuesta alto.
        // Aquí se podría usar minimax para confirmar, pero esto es un atajo.
        return {"mayor", apuestaSugerida};
    }

    // Si la mano de la IA es débil, podría apostar más y predecir "menor"
    if (sumaIA <= 8 && sumaIA > 4) { // Ejemplo: 2+3 (5), 2+4 (6), 3+4 (7)
        int apuestaSugerida = std::min(3, puntosIA);
        return {"menor", apuestaSugerida};
    }


    // Iterar sobre todas las posibles predicciones ("mayor", "menor")
    for (const auto& pred : predicciones) {
        // Iterar sobre todas las posibles apuestas (1, 2, 3)
        for (int apu : apuestas) {
            if (apu > puntosIA) continue; // La IA no puede apostar más puntos de los que tiene.

            // Ejecuta el algoritmo Minimax para cada combinación de predicción y apuesta.
            // profundidad = 1: Miramos un paso adelante (simulamos la mano del oponente).
            // esMax = true: Es el turno de la IA (maximizador).
            // Los puntos y la suma del jugador se inicializan para la simulación.
            int resultado = minimax(1, true, sumaIA, 0, pred, apu, puntosIA, 0, -100000, 100000, disponibles);

            // Si este resultado es mejor que el mejor encontrado hasta ahora, se actualiza.
            if (resultado > mejorValor) {
                mejorValor = resultado;
                mejorPrediccion = pred;
                mejorApuesta = apu;
            }
        }
    }

    // Si por alguna razón los puntos de la IA son muy bajos, podría arriesgar más.
    // Esto es una regla heurística fuera del Minimax estricto, para fomentar la agresividad
    // en ciertas situaciones.
    if (puntosIA <= 3 && mejorApuesta < 3) {
        // Podría decidir ir all-in si su mano es decente o no tiene nada que perder.
        // Aquí simplificamos a apostar lo máximo posible si los puntos son bajos.
        mejorApuesta = std::min(3, puntosIA);
    }
    else if (puntosIA >=15 && mejorApuesta <2) // Si va ganando bien, apuesta un poco más conservador
    {
        mejorApuesta = std::min(2, puntosIA);
    }


    return {mejorPrediccion, mejorApuesta};
}
