#include "MonitorPartidas.h"
#include <string>
#include <map>

MonitorPartidas::MonitorPartidas(){}

Partida* MonitorPartidas::agregarPartidaSiNoExiste(std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);

  if (partidas.find(nombre) != partidas.end()){
    throw ExcepcionServer("Se intenta crear una partida que ya existe");
  }

  Partida* nuevaPartida = new Partida();
  partidas[nombre] = nuevaPartida;
  return nuevaPartida;
}

Partida* MonitorPartidas::buscarPartidaSiExiste(const std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);
  if (partidas.find(nombre) == partidas.end()){
    throw ExcepcionServer("Se intenta unir a una partida que no existe");
  }
  return partidas[nombre];
}

std::string MonitorPartidas::listaPartidas(){
  std::lock_guard<std::mutex> lock(mtx);
  std::map<std::string, Partida*>::const_iterator it;

  std::string lista = "Partidas:\n";

  for (it = partidas.begin(); it != partidas.end(); ++it) {
  		lista += " - ";
  		lista += it->first;
  		lista += '\n';
  }
  return lista;
}

MonitorPartidas::~MonitorPartidas(){
  std::map<std::string, Partida*>::const_iterator it;
  for (it = partidas.begin(); it != partidas.end(); ++it){
    delete(it->second);
  }
}
