// Carta.h
#pragma once
#include <string>

class Carta {
public:
    std::string palo;    // "♥", "♠", "♦", "♣"
    std::string valor;   // "A", "K", "Q", "J", "10", ..., "2"
    int puntaje;         // 14 (A), 13 (K), ..., 2 (2)

    // Constructor que inicializa los miembros
    Carta(std::string p, std::string v, int pts);
};