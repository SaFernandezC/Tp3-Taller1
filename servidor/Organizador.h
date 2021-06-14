#ifndef _ORGANIZADOR_H
#define _ORGANIZADOR_H

// #include "Thread.h"
#include "Jugador.h"
#include "../common/Socket.h"
#include "MonitorPartidas.h"
#include <vector>

class Organizador{

  private:
      std::vector<Jugador*> jugadores;
      MonitorPartidas monitor_partidas;

  public:

    Organizador();

    void agregarJugador(Socket player_socket);

    ~Organizador();

  private:
    void limpiarJugadoresMuertos();
};

#endif
