// src/Jugador.h
// Define la clase Jugador, que representa a un participante en el juego (humano o IA).
// Almacena su estado actual, incluyendo puntos, mano de cartas, apuesta y predicción.
#pragma once
#include "Carta.h"
#include <vector>
#include <string>

class Jugador {
private:
    std::string nombre;      // Nombre del jugador
    std::vector<Carta> mano; // Las dos cartas en la mano
    std::string prediccion;  // La predicción de la ronda ("mayor" o "menor")
    int apuesta;             // Cantidad de puntos apostados
    int puntos;              // Puntos totales del jugador

public:
    /**
     * @brief Constructor de Jugador.
     * @param n Nombre del jugador.
     */
    Jugador(std::string n);

    /**
     * @brief Asigna dos cartas nuevas a la mano del jugador, limpiando la anterior.
     * @param c1 Primera carta.
     * @param c2 Segunda carta.
     */
    void recibirCartas(Carta c1, Carta c2);

    /**
     * @brief Calcula y devuelve la suma de los puntajes de las cartas en la mano.
     * @return La suma de los puntos de la mano.
     */
    int sumarCartas() const;

    /**
     * @brief Limpia la mano del jugador, dejándola vacía.
     */
    void limpiarMano();

    // Métodos para establecer y obtener datos (Setters y Getters)
    void setPrediccion(std::string p);
    void setApuesta(int a);

    /**
     * @brief Ajusta los puntos del jugador según el resultado de la ronda.
     * @param acierta True si el jugador acertó su predicción, false si no.
     */
    void ajustarPuntos(bool acierta);

    int getPuntos() const;
    const std::string& getNombre() const;
    const std::vector<Carta>& getMano() const;
    const std::string& getPrediccion() const;
    int getApuesta() const;
    int obtenerSumaMano() const;
};
