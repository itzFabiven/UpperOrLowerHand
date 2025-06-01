#pragma once
#include "Mazo.h"
#include "Jugador.h"
#include <list>
#include <stack>
#include <utility>

class Juego {
private:
    Mazo mazo;
    Jugador jugador;
    Jugador ia;

    std::list<Carta> cartasDescartadas;
    std::stack<std::pair<std::vector<Carta>, std::vector<Carta>>> historialManos;

public:
    Juego(std::string nombreJugador);
    void jugarRonda();
    void mostrarEstado() const;
};
