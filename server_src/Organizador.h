#ifndef _ORGANIZADOR_H
#define _ORGANIZADOR_H

#include "Jugador.h"
#include "../common_src/Socket.h"
#include "MonitorPartidas.h"
#include "ExcepcionServer.h"
#include <vector>

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error, del tipo ExcepcionServer

class Organizador{
  private:
      std::vector<Jugador*> jugadores;
      MonitorPartidas monitor_partidas;

  public:
    /*
    * Constructor
    */
    Organizador();

    /*
    * Reserva memoria y crea un nuevo jugador. Le hace start() al hilo
    * y lo agrega al vector de punteros a jugadores.
    */
    void agregarJugador(Socket player_socket);

    /*
    * Destructor. Limpia, haciendo los delete y join correspondientes
    * los jugadores que quedan validos.
    */
    ~Organizador();

  private:
    /*
    * Limpia, haciendo los delete y join correspondientes
    * los jugadores que ya no estan corriendo.
    */
    void limpiarJugadoresMuertos();
};

#endif
