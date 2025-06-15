#pragma once

#include "Carta.h"
#include <list>
#include <string>
#include <utility>
#include <vector>

class IA {
public:
    static std::pair<std::string, int> tomarDecision(int sumaIA, int puntosIA, const std::list<Carta>& cartasDescartadas, const std::vector<Carta>& manoIA);

private:
    static int evaluarEstado(int sumaIA, int sumaJugador, const std::string& prediccion, int apuesta);
    static int minimax(int profundidad, bool esMax, int sumaIA, int sumaJugador,
                       const std::string& prediccionIA, int apuestaIA,
                       int puntosIA, int puntosJugador,
                       int alpha, int beta,
                       const std::vector<Carta>& disponibles);
};

