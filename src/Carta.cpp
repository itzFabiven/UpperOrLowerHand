#include "Carta.h"


Carta::Carta(int valor, const std::string& palo)
    : valor_(valor), palo_(palo)

int Carta::obtenerValor() const {
    return valor_;
}

// Implementación de la función obtenerPalo
std::string Carta::obtenerPalo() const {
    return palo_;
}
