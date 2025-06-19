// src/Juego.h
#pragma once
#include "Jugador.h"
#include "Mazo.h"
#include "IA.h"
#include <list>
#include <utility>
#include <vector>

class Juego {
private:
    Jugador jugador;
    Jugador ia;
    Mazo mazo;
    std::list<Carta> cartasDescartadas;

    int rondaActual;
    bool partidaFinalizada;
    std::string mensajeFinalPartida;
    std::string mensajeRonda;

public:
    Juego(std::string nombreJugador);

    void iniciarNuevaRonda();
    void setApuestaJugador(int apuesta);
    void setPrediccionJugador(const std::string& prediccion);
    void resolverRonda();

    int getPuntosJugador() const;
    int getPuntosIA() const;
    int getRondaActual() const;
    const std::vector<Carta>& obtenerManoJugador() const;
    const std::vector<Carta>& obtenerManoIA() const;
    const std::string& getPrediccionIA() const;
    int getApuestaIA() const;
    bool isPartidaFinalizada() const;
    std::string getMensajeFinalPartida() const;
    void reiniciarJuego();

    int obtenerManoJugadorSuma() const;
    int obtenerManoIASuma() const; // <<< NUEVO: Para obtener la suma de la IA
    std::string getMensajeRonda() const;

private:
    void verificarFinPartida();
};