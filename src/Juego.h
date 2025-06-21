// src/Juego.h
// Define la clase Juego, que es el motor principal del juego.
// Orquesta la interacción entre los jugadores (humano y IA), el mazo y las reglas de cada ronda.
#pragma once
#include "Jugador.h"
#include "Mazo.h"
#include "IA.h"
#include <list>
#include <utility>
#include <vector>

class Juego {
private:
    Jugador jugador; // Instancia del jugador humano
    Jugador ia;      // Instancia del jugador IA
    Mazo mazo;       // El mazo de cartas
    std::list<Carta> cartasDescartadas; // Registro de cartas ya jugadas

    // Variables de estado del juego
    int rondaActual;
    bool partidaFinalizada;
    std::string mensajeFinalPartida;
    std::string mensajeRonda;

public:
    /**
     *  Constructor de la clase Juego.
     *  nombreJugador El nombre para el jugador humano.
     */
    Juego(std::string nombreJugador);

    // --- Métodos para la gestión del flujo del juego ---
    void iniciarNuevaRonda();
    void setApuestaJugador(int apuesta);
    void setPrediccionJugador(const std::string& prediccion);
    void resolverRonda();
    void reiniciarJuego();

    // --- Getters para obtener información del estado del juego ---
    int getPuntosJugador() const;
    int getPuntosIA() const;
    int getRondaActual() const;
    const std::vector<Carta>& obtenerManoJugador() const;
    const std::vector<Carta>& obtenerManoIA() const;
    const std::string& getPrediccionIA() const;
    int getApuestaIA() const;
    bool isPartidaFinalizada() const;
    std::string getMensajeFinalPartida() const;
    int obtenerManoJugadorSuma() const;
    int obtenerManoIASuma() const;
    std::string getMensajeRonda() const;

private:
    /**
     * @brief Comprueba si la partida debe terminar (por puntos o por número de rondas).
     */
    void verificarFinPartida();
};