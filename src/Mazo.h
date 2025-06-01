#pragma once
#include "Carta.h"
#include <stack>

class Mazo {
private:
    std::stack<Carta> cartas;

public:
    Mazo();
    void inicializarDobleBaraja();
    void barajar();
    Carta sacarCarta();
    bool estaVacio() const;
};


