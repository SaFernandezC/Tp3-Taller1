#include "Analizador.h"
#include <string>

#define POS_FILA 8
#define POS_COL 6
#define POS_INICIAL 0
#define MAX_FIL_COL '3'
#define MIN_FIL_COL '1'

Analizador::Analizador(){}

char Analizador::obtenerAccion(const std::string& jugada){
  if (jugada.find("crear") == POS_INICIAL){
    return CODIGO_CREAR;
  }
  if (jugada.find("unirse") == POS_INICIAL){
    return CODIGO_UNIRSE;
  }
  if (jugada.find("listar") == POS_INICIAL){
    return CODIGO_LISTAR;
  }
  if (jugada.find("jugar") == POS_INICIAL){
    return CODIGO_JUGAR;
  }
  return CODIGO_NO_VALIDO;
}

void Analizador::verificarIngreso(char& col, char& fil){
  if (col > MAX_FIL_COL || col < MIN_FIL_COL
      || fil < MIN_FIL_COL || fil > MAX_FIL_COL){
    throw ExcepcionCliente("La fila y/o la columna ingresada esta fuera"
     "de rango. Ingrese nueva jugada\n");
  }
}

void Analizador::obtenerFilaYCol(const std::string& jugada,
                                char& col, char& fil){
  if (jugada.length() < POS_FILA){
    throw ExcepcionCliente("Jugada invalida. Ingrese nueva jugada\n");
  }
  col = jugada.at(POS_COL);
  fil = jugada.at(POS_FILA);
}

std::string Analizador::obtenerNombre(const std::string& jugada,const int& pos){
  if ((int)jugada.length() < pos){
    throw ExcepcionCliente("No se pudo obtener el nombre de la partida\n");
  }
  return jugada.substr(pos);
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
