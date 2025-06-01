#include "Jugador.h"

Jugador::Jugador(std::string nombreInicial)
    : nombre(nombreInicial), puntos(5), apuesta(1), prediccion("") {}

void Jugador::recibirCartas(Carta c1, Carta c2) {
    mano.clear();
    mano.push_back(c1);
    mano.push_back(c2);
}

void Jugador::mostrarCartas() const {
    std::cout << nombre << " tiene: ";
    for (const auto& carta : mano) {
        std::cout << carta.valor << carta.palo << " (" << carta.puntaje << ") ";
    }
    std::cout << std::endl;
}

int Jugador::sumarCartas() const {
    int total = 0;
    for (const auto& carta : mano) {
        total += carta.puntaje;
    }
    return total;
}

void Jugador::setApuesta(int a) {
    apuesta = a;
}

void Jugador::setPrediccion(const std::string& p) {
    prediccion = p;
}

void Jugador::ajustarPuntos(bool acierto) {
    if (acierto) {
        puntos += apuesta;
    } else {
        puntos -= apuesta;
        if (puntos < 0) puntos = 0;
    }
}

int Jugador::getPuntos() const {
    return puntos;
}

int Jugador::getApuesta() const {
    return apuesta;
}

std::string Jugador::getPrediccion() const {
    return prediccion;
}

std::string Jugador::getNombre() const {
    return nombre;
}

void Jugador::limpiarMano() {
    mano.clear();
}

