#pragma once
#include <string>

class Carta {
public:
    std::string palo;   // "♥", "♠", etc.
    std::string valor;  // "A", "K", etc.
    int puntaje;        // 2–14

    Carta(std::string p = "", std::string v = "", int pts = 0)
        : palo(p), valor(v), puntaje(pts) {}
};
