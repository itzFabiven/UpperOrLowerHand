#include "Juego.h"
#include <iostream>

Juego::Juego(std::string nombreJugador)
    : jugador(nombreJugador), ia("IA") {}

void Juego::jugarRonda() {
    Carta j1 = mazo.sacarCarta();
    Carta j2 = mazo.sacarCarta();
    Carta ia1 = mazo.sacarCarta();
    Carta ia2 = mazo.sacarCarta();

    jugador.recibirCartas(j1, j2);
    ia.recibirCartas(ia1, ia2);

    historialManos.push({{j1, j2}, {ia1, ia2}});

    jugador.mostrarCartas();
    std::cout << "Tu puntuacion: " << jugador.sumarCartas() << std::endl;
    std::cout << "Tienes " << jugador.getPuntos() << " puntos." << std::endl;

    int apuesta;
    do {
        std::cout << "Cuantos puntos quieres apostar (1 a 3)? ";
        std::cin >> apuesta;
    } while (apuesta < 1 || apuesta > 3 || apuesta > jugador.getPuntos());
    jugador.setApuesta(apuesta);

    std::string decision;
    do {
        std::cout << "Tu mano es 'mayor' o 'menor' que la del oponente? ";
        std::cin >> decision;
    } while (decision != "mayor" && decision != "menor");
    jugador.setPrediccion(decision);

    int iaSuma = ia.sumarCartas();
    ia.setPrediccion(iaSuma > 18 ? "mayor" : "menor");
    ia.setApuesta(iaSuma > 22 ? 3 : (iaSuma > 17 ? 2 : 1));

    int sumaJugador = jugador.sumarCartas();
    int sumaIA = ia.sumarCartas();

    std::cout << "\n--- Resolucion de la ronda ---\n";
    ia.mostrarCartas();
    std::cout << "Puntuacion IA: " << sumaIA << std::endl;

    bool aciertoJugador = (decision == "mayor" && sumaJugador > sumaIA) ||
                          (decision == "menor" && sumaJugador < sumaIA);
    jugador.ajustarPuntos(aciertoJugador);

    bool aciertoIA = (ia.getPrediccion() == "mayor" && sumaIA > sumaJugador) ||
                     (ia.getPrediccion() == "menor" && sumaIA < sumaJugador);
    ia.ajustarPuntos(aciertoIA);

    cartasDescartadas.push_back(j1);
    cartasDescartadas.push_back(j2);
    cartasDescartadas.push_back(ia1);
    cartasDescartadas.push_back(ia2);

    std::cout << (aciertoJugador ? "Acertaste" : "Fallaste") << ". Tu puntaje ahora es: " << jugador.getPuntos() << std::endl;
    std::cout << "IA " << (aciertoIA ? "acerto" : "fallo") << ". Puntaje IA: " << ia.getPuntos() << "\n";
    std::cout << "-------------------------------\n";
}

void Juego::mostrarEstado() const {
    std::cout << "Estado actual - Jugador: " << jugador.getPuntos()
              << " | IA: " << ia.getPuntos() << std::endl;
}

