// src/Mazo.h
#pragma once
#include "Carta.h"
#include <stack>     // Para usar std::stack como estructura del mazo
#include <vector>    // Para el vector temporal al inicializar/barajar
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::default_random_engine
#include <chrono>    // Para std::chrono::system_clock::now().time_since_epoch().count() como seed

class Mazo {
private:
    std::stack<Carta> cartas; // El mazo como una pila (LIFO)

public:
    Mazo(); // Constructor que inicializa y baraja el mazo

    void inicializarDobleBaraja(); // Llena el mazo con dos barajas estándar
    void barajar();                // Baraja las cartas del mazo actual (si no está vacío)
    Carta sacarCarta();            // Saca la carta superior del mazo

    bool estaVacio() const;       // Verifica si el mazo está vacío
    int cantidadCartas() const;   // Devuelve la cantidad de cartas en el mazo

    // No se necesita devolverCarta en este modelo donde las descartadas no vuelven al mazo activo.
    // void devolverCarta(const Carta& carta);
};
