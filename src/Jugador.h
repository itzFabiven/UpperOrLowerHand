#pragma once
#include "Carta.h"
#include <vector>
#include <string>
#include <iostream>

class Jugador {
private:
    std::string nombre;
    int puntos;
    int apuesta;
    std::string prediccion;
    std::vector<Carta> mano;

public:
    Jugador(std::string nombreInicial);

    void recibirCartas(Carta c1, Carta c2);
    void mostrarCartas() const;
    int sumarCartas() const;

    void setApuesta(int a);
    void setPrediccion(const std::string& p);
    void ajustarPuntos(bool acierto);

    int getPuntos() const;
    int getApuesta() const;
    std::string getPrediccion() const;
    std::string getNombre() const;

    void limpiarMano();
};

