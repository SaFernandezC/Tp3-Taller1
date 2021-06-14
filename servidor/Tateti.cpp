#include "Tateti.h"

Tateti::Tateti(){
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      tablero[i][j] = ' ';
    }
  }
}

void Tateti::realizarJugada(char& caracter, int fil, int col){
  tablero[fil][col] = caracter;
}

void Tateti::construirTablero(std::string& auxiliar){
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
  auxiliar = buffer;
}

std::string Tateti::obtenerTablero(){
  std::string auxiliar;
  construirTablero(auxiliar);
  return auxiliar;
}

Tateti::~Tateti(){}
