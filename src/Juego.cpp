#include "Juego.h"
#include <iostream>
#include "IA.h"

Juego::Juego(std::string nombreJugador)
    : jugador(nombreJugador), ia("IA") {}

void Juego::jugarRonda() {
    // --- Reparto de cartas ---
    Carta j1 = mazo.sacarCarta();
    Carta j2 = mazo.sacarCarta();
    Carta ia1 = mazo.sacarCarta();
    Carta ia2 = mazo.sacarCarta();

    std::vector<Carta> manoIA = {ia1, ia2};  // mano actual de la IA
    int sumaIA = ia1.puntaje + ia2.puntaje;  // usamos las cartas reales

    // --- IA toma su decisión con Minimax + poda + cartas restantes ---
    auto [pred, apuesta] = IA::tomarDecision(sumaIA, ia.getPuntos(), cartasDescartadas, manoIA);
    ia.setPrediccion(pred);
    ia.setApuesta(apuesta);

    // --- Entregar las cartas a cada jugador ---
    jugador.recibirCartas(j1, j2);
    ia.recibirCartas(ia1, ia2);

    // --- Guardar mano completa en historial por si se requiere trazabilidad ---
    historialManos.push({{j1, j2}, {ia1, ia2}});

    // --- Mostrar mano del jugador ---
    jugador.mostrarCartas();
    std::cout << "Tu puntuacion: " << jugador.sumarCartas() << std::endl;
    std::cout << "Tienes " << jugador.getPuntos() << " puntos." << std::endl;

    // --- Apuesta del jugador ---
    int apuestaJugador;
    do {
        std::cout << "Cuantos puntos quieres apostar (1 a 3)? ";
        std::cin >> apuestaJugador;
    } while (apuestaJugador < 1 || apuestaJugador > 3 || apuestaJugador > jugador.getPuntos());
    jugador.setApuesta(apuestaJugador);

    // --- Declaración del jugador ---
    std::string decision;
    do {
        std::cout << "Tu mano es 'mayor' o 'menor' que la del oponente? ";
        std::cin >> decision;
    } while (decision != "mayor" && decision != "menor");
    jugador.setPrediccion(decision);

    // --- Resolución de la ronda ---
    int sumaJugador = jugador.sumarCartas();

    std::cout << "\n--- Resolucion de la ronda ---\n";
    ia.mostrarCartas();
    std::cout << "Puntuacion IA: " << sumaIA << std::endl;

    bool aciertoJugador = (decision == "mayor" && sumaJugador > sumaIA) ||
                          (decision == "menor" && sumaJugador < sumaIA);
    jugador.ajustarPuntos(aciertoJugador);

    bool aciertoIA = (ia.getPrediccion() == "mayor" && sumaIA > sumaJugador) ||
                     (ia.getPrediccion() == "menor" && sumaIA < sumaJugador);
    ia.ajustarPuntos(aciertoIA);

    // --- Guardar cartas como descartadas para IA futura ---
    cartasDescartadas.push_back(j1);
    cartasDescartadas.push_back(j2);
    cartasDescartadas.push_back(ia1);
    cartasDescartadas.push_back(ia2);

    // --- Resultados ---
    std::cout << (aciertoJugador ? "Acertaste" : "Fallaste")
              << ". Tu puntaje ahora es: " << jugador.getPuntos() << std::endl;
    std::cout << "IA " << (aciertoIA ? "acerto" : "fallo")
              << ". Puntaje IA: " << ia.getPuntos() << "\n";
    std::cout << "-------------------------------\n";
}

void Juego::mostrarEstado() const {
    std::cout << "Estado actual - Jugador: " << jugador.getPuntos()
              << " | IA: " << ia.getPuntos() << std::endl;
}
