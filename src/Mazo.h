// src/Mazo.h
// Define la clase Mazo, que gestiona la baraja de cartas del juego.
// Utiliza una pila (stack) para simular el comportamiento de sacar cartas de la parte superior.
#pragma once
#include "Carta.h"
#include <stack>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Mazo {
private:
    std::stack<Carta> cartas; // Pila de cartas que representa el mazo.

public:
    /**
     * Constructor de la clase Mazo.
     * Al crearse, automáticamente inicializa y baraja una doble baraja.
     */
    Mazo();

    /**
     * (Re)llena el mazo con una doble baraja estándar (104 cartas) y la baraja.
     */
    void inicializarDobleBaraja();

    /**
     * Baraja las cartas que se encuentran actualmente en el mazo.
     */
    void barajar();

    /**
     * Saca la carta superior del mazo y la devuelve.
     * La carta de la parte superior del mazo.
     */
    Carta sacarCarta();

    /**
     * Comprueba si el mazo está vacío.
     * true si el mazo no tiene cartas, false en caso contrario.
     */
    bool estaVacio() const;

    /**
     * Devuelve el número de cartas restantes en el mazo.
     * La cantidad de cartas.
     */
    int cantidadCartas() const;
};
