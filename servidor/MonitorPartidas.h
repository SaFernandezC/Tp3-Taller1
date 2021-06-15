#ifndef _MONITOR_PARTIDAS_H
#define _MONITOR_PARTIDAS_H

#include "Partida.h"
#include "ExcepcionServer.h"
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

    Partida* agregarPartidaSiNoExiste(std::string& nombre);

    Partida* buscarPartidaSiExiste(const std::string& nombre);

    std::string listaPartidas();

    // void eliminarPartida(const std::string& nombre);VER SI LA IMPLEMENTO O NO

    ~MonitorPartidas();
};

#endif
