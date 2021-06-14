#include "Tateti.h"

#define VACIO ' '

Tateti::Tateti(){
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      tablero[i][j] = VACIO;
    }
  }
  posicionesLibres = 9;
  ganador = VACIO;
  juegoTerminado = false;
}

bool Tateti::estaTerminado(){
  return juegoTerminado;
}

void Tateti::chequearFil(int& fil){
  if((tablero[fil][0] == tablero[fil][1]) && (tablero[fil][1] == tablero[fil][2])){
    juegoTerminado = true;
  }
}

void Tateti::chequearCol(int& col){
  if((tablero[0][col] == tablero[1][col]) && (tablero[1][col] == tablero[2][col])){
    juegoTerminado = true;
  }
}

void Tateti::chequearDiagonales(){
  bool cond1 = ((tablero[0][0] == tablero[1][1]) && (tablero[1][1] == tablero[2][2]) && (tablero[1][1] != VACIO));
  bool cond2 = ((tablero[2][0] == tablero[1][1]) &&  (tablero[1][1] == tablero[0][2]) && (tablero[1][1] != VACIO));

  if(cond1 || cond2){
    juegoTerminado = true;
  }
}

void Tateti::chequearGanador(int& fil, int& col){
  chequearFil(fil);
  chequearCol(col);
  chequearDiagonales();
}

void Tateti::realizarJugada(char& caracter, int fil, int col){
  if (tablero[fil][col] != VACIO) {
    return;
  }

  tablero[fil][col] = caracter;
  posicionesLibres--;

  chequearGanador(fil, col);
  if(juegoTerminado){
    ganador = caracter;
  }

  if(posicionesLibres == 0){
    juegoTerminado = true;
    return;
  }
}

void Tateti::construirTablero(std::string& tablero_aux){
  char buffer[200];
  sprintf(buffer, "    1 . 2 . 3 .\n"
					"  +---+---+---+\n"
					"1 | %c | %c | %c |\n"
					"  +---+---+---+\n"
					"2 | %c | %c | %c |\n"
					"  +---+---+---+\n"
					"3 | %c | %c | %c |\n"
					"  +---+---+---+\n",
					tablero[0][0], tablero[0][1], tablero[0][2],
					tablero[1][0], tablero[1][1], tablero[1][2],
					tablero[2][0], tablero[2][1], tablero[2][2]);
  tablero_aux = buffer;
}

void Tateti::agregarResultado(std::string& auxiliar, const char& tipoJugador) {
  if(ganador == VACIO){
    auxiliar += "Partida finaliza en empate\n";
  } else if (ganador == tipoJugador) {
    auxiliar += "Felicitaciones! Ganaste!\n";
  } else{
    auxiliar += "Perdiste!\n";
  }
}

std::string Tateti::obtenerTablero(const char& tipoJugador){
  std::string tablero_aux;
  construirTablero(tablero_aux);
  if(juegoTerminado){
    agregarResultado(tablero_aux, tipoJugador);
  }
  return tablero_aux;
}

Tateti::~Tateti(){}
