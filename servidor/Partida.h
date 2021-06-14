#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <string>
#include <mutex>
#include <condition_variable>

#include "Tateti.h"

class Partida{

  private:
    std::mutex mtx;
    std::condition_variable cambioTurno;
    char turno;
    int jugadores_conectados;
    bool jugando;
    Tateti juego;

  public:

    Partida();

    bool enJuego();

    std::string obtenerTablero(const char& tipoJugador);

    void jugar(char& tipo_jugador, char fil, char col);

    ~Partida();

  private:
    void cambiarTurno(const char& tipo_jugador);
};

#endif
