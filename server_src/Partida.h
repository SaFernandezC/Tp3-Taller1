#ifndef _PARTIDA_H
#define _PARTIDA_H

#include <string>
#include <mutex>
#include <condition_variable>

#include "Tateti.h"
#include "ExcepcionServer.h"

class Partida{
  private:
    std::mutex mtx;
    std::condition_variable cambioTurno;
    char turno;
    bool jugando;
    Tateti juego;

  public:
    /*
    * Constructor. Inicializa el tipo de jugador en JUGADOR_O
    * y cambia el estado de jugando a true.
    */
    Partida();

    /*
    * Devuelve el valor del atributo jugando.
    */
    bool enJuego();

    /*
    * Cuando sea el turno del jugador que lo solicita, le pide al
    * tateti el tablero y lo retorna.
    */
    std::string obtenerTablero(const char& tipoJugador);

    /*
    * Cuando es el turno del jugador realiza la jugada indicada,
    * de lo contrario espera a que se le notifique el cambio de turno.
    * Luego de jugar se hace el cambio de turno y se le notifica al otro usuario
    * de la partida.
    */
    void jugar(const char& tipo_jugador, char col, char fil);

    /*
    * Destructor
    */
    ~Partida();

  private:
    /*
    * Intecambia el atributo turno entre JUGADOR_O y JUGADOR_X
    * segun corresponda
    */
    void cambiarTurno(const char& tipo_jugador);

    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;
};

#endif
