#ifndef _ORGANIZADOR_H
#define _ORGANIZADOR_H

// #include "Thread.h"
#include "Jugador.h"
#include "Socket.h"
#include "MonitorPartidas.h"
#include <vector>

class Organizador{

  private:
      std::vector<Jugador*> jugadores;
      MonitorPartidas monitor_partidas;
      // MonitorPartidas monitor; //Lista de partidas
      //Y lugo cada jugador deberia tener una partida creo


  public:

    Organizador();

    void addPlayer(Socket player_socket);

    ~Organizador();

};

#endif
