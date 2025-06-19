// src/Jugador.h
#pragma once
#include "Carta.h"
#include <vector>
#include <string>

class Jugador {
private:
    std::string nombre;
    std::vector<Carta> mano;
    std::string prediccion;
    int apuesta;
    int puntos;

public:
    Jugador(std::string n);

    void recibirCartas(Carta c1, Carta c2);
    int sumarCartas() const;
    void limpiarMano();

    void setPrediccion(std::string p);
    void setApuesta(int a);
    void ajustarPuntos(bool acierta);

    int getPuntos() const;
    const std::string& getNombre() const;
    const std::vector<Carta>& getMano() const;
    const std::string& getPrediccion() const;
    int getApuesta() const;

    int obtenerSumaMano() const; // <<< NUEVO: Para obtener la suma de la mano
};
