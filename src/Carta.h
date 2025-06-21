// Carta.h
// Define la estructura de datos para una carta individual.
// Es la unidad fundamental del juego.
#pragma once
#include <string>

class Carta {
public:
    // Atributos de una carta
    std::string palo;    // El palo de la carta: "♥", "♠", "♦", "♣"
    std::string valor;   // El valor visible: "A", "K", "Q", "J", "10", ..., "2"
    int puntaje;         // El valor numérico para las comparaciones: 14 (A), 13 (K), ..., 2 (2)

    /**
     * @brief Constructor de la clase Carta.
     * @param p El palo de la carta.
     * @param v El valor de la carta (ej. "A", "10").
     * @param pts El puntaje numérico de la carta.
     */
    Carta(std::string p, std::string v, int pts);
};