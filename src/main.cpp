#include <iostream>
#include "Juego.h"

int main() {
    Juego juego("Jugador");

    for (int ronda = 1; ronda <= 10; ++ronda) {
        std::cout << "\n===== Ronda " << ronda << " =====\n";
        juego.jugarRonda();
        juego.mostrarEstado();
    }

    std::cout << "\nJuego finalizado.\n";
    return 0;
}


