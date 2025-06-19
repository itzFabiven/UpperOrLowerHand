// src/Mazo.cpp
#include "Mazo.h"
#include <stdexcept> // Para std::runtime_error
#include <iostream>  // Para depuración (puedes quitarlo si no lo necesitas)

// Constructor: inicializa y baraja el mazo al crearse.
Mazo::Mazo() {
    inicializarDobleBaraja();
    // La función inicializarDobleBaraja ya baraja, así que no es necesario llamar a barajar() aquí de nuevo.
}

// Llena el mazo con dos barajas estándar y las baraja.
void Mazo::inicializarDobleBaraja() {
    // Vaciar el mazo actual antes de rellenar
    while (!cartas.empty()) {
        cartas.pop();
    }

    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    // Se ajustan los puntajes para que 'A' sea 14 y 'K' sea 13, como se indicó en Carta.h
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    std::vector<Carta> tempCartas; // Vector temporal para construir y barajar el mazo

    for (int i = 0; i < 2; ++i) { // Iterar dos veces para doble baraja (104 cartas)
        for (auto& p : palos) {
            for (auto& v : valores) {
                tempCartas.emplace_back(p, v.first, v.second); // Añadir cada carta al vector temporal
            }
        }
    }

    // Barajar las cartas en el vector temporal
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tempCartas.begin(), tempCartas.end(), std::default_random_engine(seed));

    // Devolver las cartas barajadas a la pila
    for (const auto& carta : tempCartas) {
        cartas.push(carta);
    }
}

// Baraja las cartas del mazo actual.
// Actualmente, la inicialización ya las baraja. Este método podría ser útil si se quisiera re-barajar
// el mazo sin volver a llenarlo, pero dado el tamaño de las 2 barajas y el modelo de descarte,
// no es estrictamente necesario que se llame de forma independiente en cada ronda.
void Mazo::barajar() {
    if (cartas.empty()) {
        std::cout << "El mazo está vacío, no se puede barajar." << std::endl;
        return;
    }

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
        // En un juego real, esto debería ser manejado por la lógica del juego (Juego.cpp)
        // lanzando una excepción que GameScreen pueda capturar y actuar en consecuencia
        // (por ejemplo, terminar la partida por falta de cartas si es una condición de juego).
        // Sin embargo, según lo discutido, es poco probable que suceda con 2 barajas y 10 rondas.
        throw std::runtime_error("No hay más cartas en el mazo.");
    }
    Carta cartaSacada = cartas.top();
    cartas.pop();
    return cartaSacada;
}

// Verifica si el mazo está vacío.
bool Mazo::estaVacio() const {
    return cartas.empty();
}

// Devuelve la cantidad de cartas en el mazo.
int Mazo::cantidadCartas() const {
    return cartas.size();
}

// El método devolverCarta ya no es necesario si las cartas no se reutilizan dentro de la misma partida.
// Si se reutilizaran para una NUEVA partida, sería parte de la lógica de reinicio del juego.