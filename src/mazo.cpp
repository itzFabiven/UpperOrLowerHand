#include "Mazo.h"
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <stdexcept>

Mazo::Mazo() {
    inicializarDobleBaraja();
    barajar();
}

void Mazo::inicializarDobleBaraja() {
    std::vector<Carta> vectorCartas;
    std::vector<std::string> palos = {"♥", "♠", "♦", "♣"};
    std::vector<std::pair<std::string, int>> valores = {
        {"A", 14}, {"K", 13}, {"Q", 12}, {"J", 11},
        {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7},
        {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}
    };

    for (int i = 0; i < 2; ++i) {
        for (auto& palo : palos) {
            for (auto& valor : valores) {
                vectorCartas.emplace_back(palo, valor.first, valor.second);
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vectorCartas.begin(), vectorCartas.end(), g);

    for (const auto& carta : vectorCartas) {
        cartas.push(carta);
    }
}

void Mazo::barajar() {
    // No es necesario, ya se baraja al cargar
}

Carta Mazo::sacarCarta() {
    if (!cartas.empty()) {
        Carta c = cartas.top();
        cartas.pop();
        return c;
    } else {
        throw std::out_of_range("El mazo está vacío");
    }
}

bool Mazo::estaVacio() const {
    return cartas.empty();
}
