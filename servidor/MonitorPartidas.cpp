#include "MonitorPartidas.h"



MonitorPartidas::MonitorPartidas(){}

Partida* MonitorPartidas::agregarPartida(std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);

  Partida* nuevaPartida = new Partida();
  partidas[nombre] = nuevaPartida;
  return nuevaPartida;
}

bool MonitorPartidas::existePartida(std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);
  if(partidas.find(nombre) != partidas.end()){
    return true;
  }
  return false;
}

Partida* MonitorPartidas::buscarPartida(const std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);
  return partidas[nombre];
}

std::string MonitorPartidas::listaPartidas(){
  std::lock_guard<std::mutex> lock(mtx);
  std::map<std::string, Partida*>::const_iterator it;

  std::string lista = "Partidas:";

  for (it = partidas.begin(); it != partidas.end(); ++it){
    lista += "\n";
    lista += " - ";
    lista += it->first;
  }
  return lista;
}

void MonitorPartidas::eliminarPartida(const std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);
  delete(partidas[nombre]);
  partidas.erase(nombre);
}


MonitorPartidas::~MonitorPartidas(){
  std::map<std::string, Partida*>::const_iterator it;
  for (it = partidas.begin(); it != partidas.end(); ++it){
    delete(it->second);
  }
}
