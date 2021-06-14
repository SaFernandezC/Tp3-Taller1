#include "Partida.h"



Partida::Partida(){
  turno = JUGADOR_X;
  jugando = true;
}

bool Partida::enJuego(){
  std::unique_lock<std::mutex> lock(mtx);
  return jugando;
}

std::string Partida::obtenerTablero(){
  std::unique_lock<std::mutex> lock(mtx);
  return juego.obtenerTablero();
}

void Partida::cambiarTurno(const char& tipo_jugador){
  if(tipo_jugador == JUGADOR_X){
    turno = JUGADOR_O;
  } else{
    turno = JUGADOR_X;
  }
}

void Partida::jugar(char& tipo_jugador, char fil, char col){
  std::unique_lock<std::mutex> lock(mtx);
  while (turno != tipo_jugador) {
    cambioTurno.wait(lock);
  }
  juego.realizarJugada(tipo_jugador, (int)fil, (int)col);
  cambiarTurno(tipo_jugador);
  //Aca veo si alguien gano
  // jugando = juego.sigueJugando();
  cambioTurno.notify_all();
}

Partida::~Partida(){}
