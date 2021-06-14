#include "Analizador.h"

#define POS_FILA 6
#define POS_COL 8

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

void Analizador::obtenerFilaYCol(const std::string& jugada, char& fila, char& col){
  try{
    fila = jugada.at(POS_FILA);
    col = jugada.at(POS_COL);
  } catch(...){
    std::cout << "Jugada Invalida, no se puede obtener fila y col" << '\n'; //CAMBIARRRRRRRRRRRRRRRRRRRRRR
  }
}

std::string Analizador::obtenerNombre(const std::string& jugada, const int& pos){
  return jugada.substr(pos); //Aca lanzar excepcion
}

bool Analizador::partidaFinalizada(const std::string& tablero){
  return true;
}

Analizador::~Analizador(){}
