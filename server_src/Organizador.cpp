#include "Organizador.h"
#include <utility>

Organizador::Organizador(){}

void Organizador::limpiarJugadoresMuertos(){
  for (unsigned int i = 0; i < jugadores.size(); i++) {
    if (jugadores[i]->corriendo() == false){
      jugadores[i]->stop();
      jugadores[i]->join();
      delete jugadores[i];
      jugadores.erase(jugadores.begin() + i);
    }
  }
}

void Organizador::agregarJugador(Socket player_socket){
  Jugador* jugador = new Jugador(std::move(player_socket), monitorPartidas);
  if (!jugador){
    throw ExcepcionServer("Error en el new de un nuevo jugador");
  }
  jugador->start();
  jugadores.push_back(jugador);
  limpiarJugadoresMuertos();
}

Organizador::~Organizador(){
  for (unsigned int i = 0; i < jugadores.size(); i++) {
    jugadores[i]->stop();
    jugadores[i]->join();
    delete jugadores[i];
  }
}
