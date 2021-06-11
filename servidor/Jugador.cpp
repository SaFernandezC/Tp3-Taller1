#include "Jugador.h"


Jugador::Jugador(Socket player_sock):player_socket(std::move(player_sock)){
}

void Jugador::run(){

  //va la logica de recivir mensajes

}

Jugador::~Jugador(){
  player_socket.close();
}
