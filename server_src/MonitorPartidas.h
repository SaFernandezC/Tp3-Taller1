#ifndef _MONITOR_PARTIDAS_H
#define _MONITOR_PARTIDAS_H

#include "Partida.h"
#include "ExcepcionServer.h"
#include <mutex>
#include <string>
#include <map>

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error, de tipo ExcepcionServer

class MonitorPartidas{
  private:
    std::map<std::string, Partida*> partidas;
    std::mutex mtx;

  public:
    /*
    * Constructor
    */
    MonitorPartidas();

    /*
    * Si no existe una partida con el nombre dado, la crea
    * y la inserta al map.
    */
    Partida* agregarPartidaSiNoExiste(std::string& nombre);

    /*
    * Si existe una partida con el nombre dado, devuelve el
    * ptr a la misma.
    */
    Partida* buscarPartidaSiExiste(const std::string& nombre);

    /*
    * Itera el mapa creando una lista de partidas en forma
    *de string y luego la retorna
    */
    std::string listaPartidas();

    /*
    * Destructor. Hace el delete de todas las partidas del map;
    */
    ~MonitorPartidas();

  private:
    MonitorPartidas(const MonitorPartidas&) = delete;
    MonitorPartidas& operator=(const MonitorPartidas&) = delete;
};

#endif
