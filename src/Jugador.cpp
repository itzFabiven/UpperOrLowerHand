// src/Jugador.cpp
#include "Jugador.h"

Jugador::Jugador(std::string n) : nombre(n), puntos(10), apuesta(0) {
}

void Jugador::recibirCartas(Carta c1, Carta c2) {
    mano.clear();
    mano.push_back(c1);
    mano.push_back(c2);
}

int Jugador::sumarCartas() const {
    if (mano.size() == 2) {
        return mano[0].puntaje + mano[1].puntaje;
    }
    return 0;
}

void Jugador::limpiarMano() {
    mano.clear();
}

void Jugador::setPrediccion(std::string p) {
    prediccion = p;
}

void Jugador::setApuesta(int a) {
    apuesta = a;
}

void Jugador::ajustarPuntos(bool acierta) {
    if (acierta) {
        puntos += apuesta;
    } else {
        puntos -= apuesta;
    }
    if (puntos < 0) {
        puntos = 0;
    }
}

int Jugador::getPuntos() const {
    return puntos;
}

const std::string& Jugador::getNombre() const {
    return nombre;
}

const std::vector<Carta>& Jugador::getMano() const {
    return mano;
}

const std::string& Jugador::getPrediccion() const {
    return prediccion;
}

int Jugador::getApuesta() const {
    return apuesta;
}

// <<< NUEVO: Definición de la función para obtener la suma
int Jugador::obtenerSumaMano() const {
    if (mano.size() == 2) {
        return mano[0].puntaje + mano[1].puntaje;
    }
    return 0;
}
