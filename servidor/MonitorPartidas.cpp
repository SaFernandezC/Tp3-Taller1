#include "MonitorPartidas.h"



MonitorPartidas::MonitorPartidas(){}

Partida* MonitorPartidas::agregarPartida(std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);

  Partida* nuevaPartida;

  try{
    nuevaPartida = partidas.at(nombre);
  }catch(...){ //Si catchea una excepcion es que ni existe la partida;
    nuevaPartida = new Partida();
    partidas[nombre] = nuevaPartida;
    return nuevaPartida;
  }

  throw("Intenta crear partida ya existente\n"); //Leer sobre out_of_range exception

}

Partida* MonitorPartidas::buscarPartida(const std::string& nombre){
  std::lock_guard<std::mutex> lock(mtx);

  Partida* partida;
  try{
    partida = partidas[nombre];
  } catch(std::exception& e){
    throw("Aca va una excepcion de que no existe la partida (monitorpartidas)\n");
  }

  //Ver si aca devuelvo cuando ya tiene dos jugadores

  return partida;
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

}
