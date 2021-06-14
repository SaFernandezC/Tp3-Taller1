#include "Analizador.h"

#define POS_FILA 8
#define POS_COL 6

Analizador::Analizador(){}

char Analizador::obtenerAccion(const std::string& jugada){
  if(jugada.find("crear") == 0){
    return CODIGO_CREAR;
  }
  if(jugada.find("unirse") == 0){
    return CODIGO_UNIRSE;
  }
  if(jugada.find("listar") == 0){
    return CODIGO_LISTAR;
  }
  if(jugada.find("jugar") == 0){
    return CODIGO_JUGAR;
  }
  return CODIGO_NO_VALIDO;
}

void Analizador::obtenerFilaYCol(const std::string& jugada, char& col, char& fil){
  try{
    col = jugada.at(POS_COL);
    fil = jugada.at(POS_FILA);
  } catch(...){
    std::cout << "Jugada Invalida, no se puede obtener fila y col" << '\n'; //CAMBIARRRRRRRRRRRRRRRRRRRRRR
  }
}

std::string Analizador::obtenerNombre(const std::string& jugada, const int& pos){
  return jugada.substr(pos); //Aca lanzar excepcion
}

bool Analizador::partidaFinalizada(const std::string& tablero){

  if (tablero.find("Ganaste!") != std::string::npos ||
      tablero.find("Perdiste!") != std::string::npos ||
      tablero.find("empate") != std::string::npos) {
    return true;
  }

  return false;
}

Analizador::~Analizador(){}
