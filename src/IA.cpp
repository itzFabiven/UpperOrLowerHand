#include "IA.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

int IA::evaluarEstado(int sumaIA, int sumaJugador, const std::string& prediccion, int apuesta) {
    if (sumaIA == sumaJugador) return 0;

    bool acierto = (prediccion == "mayor" && sumaIA > sumaJugador) ||
                   (prediccion == "menor" && sumaIA < sumaJugador);

    return acierto ? apuesta : -apuesta;
}

std::vector<Carta> obtenerCartasDisponibles(const std::list<Carta>& descartadas, const std::vector<Carta>& manoIA) {
    std::vector<Carta> todas;
    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    for (int i = 0; i < 2; ++i) {
        for (const auto& palo : palos) {
            for (const auto& valor : valores) {
                todas.emplace_back(palo, valor.first, valor.second);
            }
        }
    }

    std::list<Carta> usadas = descartadas;
    usadas.insert(usadas.end(), manoIA.begin(), manoIA.end());

    std::vector<Carta> disponibles;
    for (const auto& carta : todas) {
        auto it = std::find_if(usadas.begin(), usadas.end(), [&](const Carta& usada) {
            return carta.palo == usada.palo && carta.valor == usada.valor;
        });

        if (it != usadas.end()) {
            usadas.erase(it); // eliminar solo una copia
        } else {
            disponibles.push_back(carta);
        }
    }

    return disponibles;
}

int IA::minimax(int profundidad, bool esMax, int sumaIA, int sumaJugador,
                const std::string& prediccionIA, int apuestaIA,
                int puntosIA, int puntosJugador,
                int alpha, int beta,
                const std::vector<Carta>& disponibles) {
    if (profundidad == 0) {
        return evaluarEstado(sumaIA, sumaJugador, prediccionIA, apuestaIA);
    }

    if (esMax) {
        int maxEval = -1000;
        for (size_t i = 0; i < disponibles.size(); ++i) {
            for (size_t j = i + 1; j < disponibles.size(); ++j) {
                int sumaSim = disponibles[i].puntaje + disponibles[j].puntaje;
                int eval = minimax(0, false, sumaIA, sumaSim, prediccionIA, apuestaIA,
                                   puntosIA, puntosJugador, alpha, beta, disponibles);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    } else {
        return -minimax(0, true, sumaIA, sumaJugador, prediccionIA, apuestaIA,
                        puntosIA, puntosJugador, alpha, beta, disponibles);
    }
}

std::pair<std::string, int> IA::tomarDecision(int sumaIA, int puntosIA, const std::list<Carta>& cartasDescartadas, const std::vector<Carta>& manoIA) {
    std::vector<std::string> predicciones = {"mayor", "menor"};
    std::vector<int> apuestas = {1, 2, 3};
    std::vector<Carta> disponibles = obtenerCartasDisponibles(cartasDescartadas, manoIA);

    int mejorValor = -1000;
    std::string mejorPrediccion = "mayor";
    int mejorApuesta = 1;

    if (sumaIA == 28) return {"mayor", std::min(3, puntosIA)};
    if (sumaIA == 4)  return {"menor", std::min(3, puntosIA)};

    for (const auto& pred : predicciones) {
        for (int apu : apuestas) {
            if (apu > puntosIA) continue;

            int resultado = minimax(1, true, sumaIA, 0, pred, apu, puntosIA, 0, -1000, 1000, disponibles);
            if (resultado > mejorValor) {
                mejorValor = resultado;
                mejorPrediccion = pred;
                mejorApuesta = apu;
            }
        }
    }

    return {mejorPrediccion, mejorApuesta};
}
