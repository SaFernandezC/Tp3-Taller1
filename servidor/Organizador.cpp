#include "Organizador.h"

Organizador::Organizador(){}

void Organizador::addPlayer(Socket player_socket){ //VVER SI RECIBO SOCKET O SOCKET&&
  jugadores.push_back(new Jugador(std::move(player_socket)));
}

Organizador::~Organizador(){
  for (unsigned int i = 0; i < jugadores.size(); i++) {
    delete jugadores[i];
    // jugadores.erase(jugadores.begin() + i);
  }
}
