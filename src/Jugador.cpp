// src/Jugador.cpp
// Implementación de los métodos de la clase Jugador.
#include "Jugador.h"

// Constructor: inicializa el nombre y los puntos (10 por defecto al inicio).
Jugador::Jugador(std::string n) : nombre(n), puntos(10), apuesta(0) {
}

// Recibe dos cartas y las asigna a la mano del jugador.
void Jugador::recibirCartas(Carta c1, Carta c2) {
    mano.clear(); // Se asegura de que la mano esté vacía antes de añadir nuevas.
    mano.push_back(c1);
    mano.push_back(c2);
}

// Suma el puntaje de las cartas en la mano.
int Jugador::sumarCartas() const {
    if (mano.size() == 2) {
        return mano[0].puntaje + mano[1].puntaje;
    }
    return 0; // Si no hay 2 cartas, la suma es 0.
}

// Limpia las cartas de la mano del jugador.
void Jugador::limpiarMano() {
    mano.clear();
}

// Establece la predicción del jugador.
void Jugador::setPrediccion(std::string p) {
    prediccion = p;
}

// Establece la apuesta del jugador.
void Jugador::setApuesta(int a) {
    apuesta = a;
}

// Ajusta los puntos del jugador. Suma si acierta, resta si falla.
void Jugador::ajustarPuntos(bool acierta) {
    if (acierta) {
        puntos += apuesta;
    } else {
        puntos -= apuesta;
    }
    // Se asegura de que los puntos no sean negativos.
    if (puntos < 0) {
        puntos = 0;
    }
}

// Getters para obtener los valores de los atributos privados.
int Jugador::getPuntos() const { return puntos; }
const std::string& Jugador::getNombre() const { return nombre; }
const std::vector<Carta>& Jugador::getMano() const { return mano; }
const std::string& Jugador::getPrediccion() const { return prediccion; }
int Jugador::getApuesta() const { return apuesta; }
int Jugador::obtenerSumaMano() const { return sumarCartas(); }
