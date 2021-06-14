#ifndef _MONITOR_PARTIDAS_H
#define _MONITOR_PARTIDAS_H

#include "Partida.h"
#include <mutex>
#include <string>
#include <map>


//Lock_guard si no uso condition variable
//Unique lock si uso condition variable

class MonitorPartidas{

  private:
    std::map<std::string, Partida*> partidas;
    std::mutex mtx;


  public:

    MonitorPartidas();

    Partida* agregarPartida(std::string& nombre);

    bool existePartida(std::string& nombre);

    Partida* buscarPartida(const std::string& nombre); //Ver si uso puntero o referencia

    std::string listaPartidas();

    void eliminarPartida(const std::string& nombre);

    ~MonitorPartidas();



};

#endif
