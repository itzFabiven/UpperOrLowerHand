// src/Juego.cpp
// Implementación de la lógica principal y las reglas del juego.
#include "Juego.h"
#include "IA.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <SFML/System/String.hpp>


// El constructor inicializa los jugadores, la ronda y otros estados.
Juego::Juego(std::string nombreJugador)
    : jugador(nombreJugador), ia("IA"), rondaActual(1), partidaFinalizada(false), mensajeFinalPartida(""), mensajeRonda("")
{
    // El mazo se crea e inicializa automáticamente gracias a su propio constructor.
}

// Prepara todo para el inicio de una nueva ronda.
void Juego::iniciarNuevaRonda() {
    if (partidaFinalizada) {
        return;
    }
    // Limpia las manos de la ronda anterior.
    jugador.limpiarMano();
    ia.limpiarMano();
    mensajeRonda = "";

    // Reparte dos cartas a cada jugador.
    Carta j1 = mazo.sacarCarta();
    Carta j2 = mazo.sacarCarta();
    Carta ia1 = mazo.sacarCarta();
    Carta ia2 = mazo.sacarCarta();
    jugador.recibirCartas(j1, j2);
    ia.recibirCartas(ia1, ia2);

    // La IA toma su decisión de forma automática al inicio de la ronda.
    std::pair<std::string, int> iaDecision = IA::tomarDecision(
        ia.sumarCartas(), ia.getPuntos(), cartasDescartadas, ia.getMano()
    );
    ia.setPrediccion(iaDecision.first);
    ia.setApuesta(iaDecision.second);
}

// Establece la apuesta del jugador, con validaciones.
void Juego::setApuestaJugador(int apuesta) {
    if (apuesta <= jugador.getPuntos() && apuesta > 0) {
        jugador.setApuesta(apuesta);
    } else {
        jugador.setApuesta(std::min(apuesta, jugador.getPuntos()));
        if (jugador.getApuesta() == 0 && jugador.getPuntos() > 0) {
             jugador.setApuesta(1);
        } else if (jugador.getPuntos() == 0) {
            jugador.setApuesta(0);
        }
    }
}

// Establece la predicción del jugador.
void Juego::setPrediccionJugador(const std::string& prediccion) {
    jugador.setPrediccion(prediccion);
}

// Resuelve la ronda: compara manos, ajusta puntos y actualiza el estado.
void Juego::resolverRonda() {
    int sumaJugador = jugador.sumarCartas();
    int sumaIA = ia.sumarCartas();

    // Evalúa si cada jugador acertó su predicción de forma independiente.
    bool aciertoJugador = (jugador.getPrediccion() == "mayor" && sumaJugador > sumaIA) ||
                          (jugador.getPrediccion() == "menor" && sumaJugador < sumaIA);

    bool aciertoIA = (ia.getPrediccion() == "mayor" && sumaIA > sumaJugador) ||
                     (ia.getPrediccion() == "menor" && sumaIA < sumaJugador);

    // Si las sumas son iguales, ninguna predicción de "mayor" o "menor" puede ser correcta.
    if (sumaJugador == sumaIA) {
        aciertoJugador = false;
        aciertoIA = false;
    }

    // Ajusta los puntos de cada uno basado en su propio resultado.
    jugador.ajustarPuntos(aciertoJugador);
    ia.ajustarPuntos(aciertoIA);

    // Genera el mensaje de resultado de la ronda.
    std::string tempMsg;
    if (aciertoJugador && aciertoIA) {
        tempMsg = "¡Ambos acertaron!";
    } else if (aciertoJugador && !aciertoIA) {
        tempMsg = "¡Acertaste tu prediccion!";
    } else if (!aciertoIA && aciertoIA) {
        tempMsg = "La IA acerto su prediccion.";
    } else {
        tempMsg = "Nadie acerto.";
    }
    mensajeRonda = sf::String::fromUtf8(tempMsg.begin(), tempMsg.end());

    // Mueve las cartas jugadas al montón de descarte.
    cartasDescartadas.push_back(jugador.getMano()[0]);
    cartasDescartadas.push_back(jugador.getMano()[1]);
    cartasDescartadas.push_back(ia.getMano()[0]);
    cartasDescartadas.push_back(ia.getMano()[1]);

    rondaActual++;
    verificarFinPartida(); // Comprueba si el juego ha terminado.
}

// Comprueba las condiciones de fin de partida.
void Juego::verificarFinPartida() {
    std::string tempMsg;
    bool fin = false;
    if (jugador.getPuntos() <= 0) {
        partidaFinalizada = true;
        tempMsg = "¡Has perdido! Te quedaste sin puntos.";
        fin = true;
    } else if (ia.getPuntos() <= 0) {
        partidaFinalizada = true;
        tempMsg = "¡Has ganado! La IA se quedo sin puntos.";
        fin = true;
    } else if (rondaActual > 10) {
        partidaFinalizada = true;
        if (jugador.getPuntos() > ia.getPuntos()) {
            tempMsg = "¡Juego terminado! Has ganado por puntos.";
        } else if (ia.getPuntos() > jugador.getPuntos()) {
            tempMsg = "¡Juego terminado! La IA ha ganado por puntos.";
        } else {
            tempMsg = "¡Juego terminado! Empate en puntos.";
        }
        fin = true;
    }
    if (fin) {
        mensajeFinalPartida = sf::String::fromUtf8(tempMsg.begin(), tempMsg.end());
    }
}

// Reinicia el juego a su estado inicial.
void Juego::reiniciarJuego() {
    jugador = Jugador(jugador.getNombre());
    ia = Jugador("IA");
    cartasDescartadas.clear();
    mazo.inicializarDobleBaraja();
    rondaActual = 1;
    partidaFinalizada = false;
    mensajeFinalPartida = "";
    mensajeRonda = "";
    jugador.limpiarMano();
    ia.limpiarMano();
}

// Getters para que la interfaz pueda acceder a la información del juego.
int Juego::getPuntosJugador() const { return jugador.getPuntos(); }
int Juego::getPuntosIA() const { return ia.getPuntos(); }
int Juego::getRondaActual() const { return rondaActual; }
const std::vector<Carta>& Juego::obtenerManoJugador() const { return jugador.getMano(); }
const std::vector<Carta>& Juego::obtenerManoIA() const { return ia.getMano(); }
const std::string& Juego::getPrediccionIA() const { return ia.getPrediccion(); }
int Juego::getApuestaIA() const { return ia.getApuesta(); }
bool Juego::isPartidaFinalizada() const { return partidaFinalizada; }
std::string Juego::getMensajeFinalPartida() const { return mensajeFinalPartida; }
int Juego::obtenerManoJugadorSuma() const { return jugador.obtenerSumaMano(); }
int Juego::obtenerManoIASuma() const { return ia.obtenerSumaMano(); }
std::string Juego::getMensajeRonda() const { return mensajeRonda; }