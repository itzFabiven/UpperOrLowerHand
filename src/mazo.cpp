// src/Mazo.cpp
// Implementación de los métodos de la clase Mazo.
#include "Mazo.h"
#include <stdexcept>
#include <iostream>

// Constructor: se llama automáticamente al crear un objeto Mazo.
Mazo::Mazo() {
    inicializarDobleBaraja();
}

// Llena el mazo con dos barajas estándar y las baraja.
void Mazo::inicializarDobleBaraja() {
    // Se asegura de que el mazo esté vacío antes de llenarlo.
    while (!cartas.empty()) {
        cartas.pop();
    }

    // Definición de los palos y valores para crear las cartas.
    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    // Usamos un vector temporal para poder barajar las cartas fácilmente.
    std::vector<Carta> tempCartas;
    tempCartas.reserve(104); // Reservamos espacio para optimizar.

    // Bucle para crear dos barajas completas (52 * 2 = 104 cartas).
    for (int i = 0; i < 2; ++i) {
        for (auto& p : palos) {
            for (auto& v : valores) {
                tempCartas.emplace_back(p, v.first, v.second);
            }
        }
    }

    // Se baraja el vector temporal usando un generador de números aleatorios.
    // La semilla se basa en el reloj del sistema para asegurar un barajado diferente cada vez.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tempCartas.begin(), tempCartas.end(), std::default_random_engine(seed));

    // Se pasan las cartas barajadas del vector a la pila (el mazo final).
    for (const auto& carta : tempCartas) {
        cartas.push(carta);
    }
}

// Baraja las cartas que ya están en el mazo.
void Mazo::barajar() {
    if (cartas.empty()) {
        return;
    }

    // Para barajar una pila, la pasamos a un vector, barajamos el vector y lo devolvemos a la pila.
    std::vector<Carta> tempCartas;
    while (!cartas.empty()) {
        tempCartas.push_back(cartas.top());
        cartas.pop();
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tempCartas.begin(), tempCartas.end(), std::default_random_engine(seed));

    for (const auto& carta : tempCartas) {
        cartas.push(carta);
    }
}

// Saca la carta superior del mazo.
Carta Mazo::sacarCarta() {
    if (cartas.empty()) {
        // Esta situación es poco probable con 104 cartas, pero es una buena práctica manejarla.
        throw std::runtime_error("No hay mas cartas en el mazo.");
    }
    Carta cartaSacada = cartas.top();
    cartas.pop();
    return cartaSacada;
}

// Devuelve true si el mazo está vacío.
bool Mazo::estaVacio() const {
    return cartas.empty();
}

// Devuelve el número de cartas restantes.
int Mazo::cantidadCartas() const {
    return cartas.size();
}