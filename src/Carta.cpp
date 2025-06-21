// Carta.cpp
// Implementación del constructor de la clase Carta.
#include "Carta.h"

// El constructor inicializa los miembros de la clase con los valores pasados como parámetros.
Carta::Carta(std::string p, std::string v, int pts)
    : palo(p), valor(v), puntaje(pts) {}