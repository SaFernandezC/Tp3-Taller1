#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <string>
#include <mutex>
#include <condition_variable>

#include "Tateti.h"

class Partida{

  private:
    std::mutex mtx;
    std::condition_variable cambio_turno;
    int jugadores_conectados;
    Tateti juego;

  public:

    Partida();

    ~Partida();
    
    //
    // Partida(Partida&& other){}
    //
    // Partida& operator=(Partida&& other){
    //   return *this;
    // }
    // Partida(const Partida&)=default;
    // Partida& operator=(const Partida&)=default;

};

#endif
