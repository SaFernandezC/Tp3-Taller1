#include "Organizador.h"

Organizador::Organizador(){}

void Organizador::limpiarJugadoresMuertos(){
  for (unsigned int i = 0; i < jugadores.size(); i++) {
    if(jugadores[i]->corriendo() == false){
      jugadores[i]->stop();
      jugadores[i]->join();
      delete jugadores[i];
    }
  }
}

void Organizador::agregarJugador(Socket player_socket){
  Jugador* jugador = new Jugador(std::move(player_socket), monitor_partidas);  //Ver que onda si falla el new
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
