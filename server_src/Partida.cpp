#include "Partida.h"
#include <string>

Partida::Partida(){
  turno = JUGADOR_O;
  jugando = true;
}

bool Partida::enJuego(){
  std::unique_lock<std::mutex> lock(mtx);
  return jugando;
}

std::string Partida::obtenerTablero(const char& tipoJugador){
  std::unique_lock<std::mutex> lock(mtx);
  while ((turno != tipoJugador) && (jugando == true)) {
    cambioTurno.wait(lock);
  }
  return juego.obtenerTablero(tipoJugador);
}

void Partida::cambiarTurno(const char& tipoJugador){
  if (tipoJugador == JUGADOR_X){
    turno = JUGADOR_O;
  } else{
    turno = JUGADOR_X;
  }
}

void Partida::jugar(const char& tipoJugador, char col, char fil){
  std::unique_lock<std::mutex> lock(mtx);
  while (turno != tipoJugador) {
    cambioTurno.wait(lock);
  }
  juego.realizarJugada(tipoJugador, (int)fil, (int)col);
  cambiarTurno(tipoJugador);
  jugando = !juego.estaTerminado();
  cambioTurno.notify_all();
}

Partida::~Partida(){}
