#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <atomic>
#include "Thread.h"
#include "MonitorPartidas.h"
#include "../common_src/Socket.h"
#include "../common_src/Protocolo.h"

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error

class Jugador: public Thread{
  private:
    Socket socketJugador;
    MonitorPartidas& monitorPrtidas;
    Partida* partidaActual;
    char tipoJugador;
    std::atomic<bool> estaCorriendo;

  public:
    /*
    * Constructor, inicializa partidaActual en nulo y tipoJugador
    * en VACIO;
    */
    Jugador(Socket player_sock, MonitorPartidas& monitor);

    /*
    * Realiza la logia del las jugadas, envio y recepcion
    *de mensajes, hasta que la parida termine o haya algun error.
    */
    virtual void run() override;

    /*
    * Retorna si el jugador sigue corriendo o no.
    */
    bool corriendo() const;

    /*
    * Cambia el estado de estaCorriendo. Hace un shutdown y close
    * del socketJugador
    */
    void stop();

    /*
    * Cierra el socketJugador;
    */
    ~Jugador();

  private:
    /*
    * Recibe un nombre a traves del protocolo e intenta
    * crear una partida con ese nombre. Asgina el tipo de
    * jugador a JUGADOR_O. Retorna true si la conexion
    * fue exitosa
    */
    bool crear_partida(Protocolo& protocolo);

    /*
    * Recibe un nombre a traves del protocolo e intenta
    * unirse una partida con ese nombre. Asgina el tipo de
    * jugador a JUGADOR_X. Retorna true si la conexion
    * fue exitosa
    */
    bool unirse_partida(Protocolo& protocolo);

    /*
    * Obtiene la lista de partidas desde el monitorPrtidas
    * y la envia al cliente a traves del protocolo
    */
    void listar_partidas(Protocolo& protocolo);

    /*
    * Realiza un loop hasta que el jugador haya creado una
    * partida o se haya unido a una existente.
    */
    void entrarAPartida(Protocolo& protocolo);

    /*
    * Realiza un loop hasta que la partida termine, enviando
    * y recibiendo mensajes de jugada y tablero. Interactua con
    * la partida para realizar las jugadas y obtener el tablero.
    */
    void jugarPartida(Protocolo& protocolo);
};

#endif
