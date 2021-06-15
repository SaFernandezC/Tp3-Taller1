#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H

#include "Socket.h"
#include "ExcepcionSocket.h"
#include <string>

#define CODIGO_JUGAR 0x70
#define CODIGO_LISTAR 0x6C
#define CODIGO_CREAR 0x6E
#define CODIGO_UNIRSE 0x6A

class Protocolo{
  public:
    /*
    * Constructor
    */
    Protocolo();

    /*
    * Recibe mediante el socket 1byte correspondiente al
    * codigo de accion a realizar
    */
    void recvTipoAccion(Socket& socket, char& tipo_accion);

    /*
    * Envia mediante el socket 1 byte con el codigo de crear
    * o unirse segun corresponda, luego envia el nombre de la
    * partida
    */
    void enviarCrearUnirse(Socket& socket, const char& codigoAccion,
                          std::string& nombre);

    /*
    * Envia mediante el socket 1 byte con el codigo de listar
    */
    void enviarListar(Socket& socket, const char& codigoListar);

    /*
    * Le indica al socket que envie el largo del mensaje que
    *recibe por parametro y luego el mensaje
    */
    void enviarMensaje(Socket& socket, const std::string& mensaje);

    /*
    * Le indica al socket que reciba el largo del mensaje que
    *recibe por parametro y luego el mensaje
    */
    void recvMensaje(Socket& socket, std::string& mensaje);

    /*
    * Le indica al socket que envie 1 byte con el codigo de
    *jugada y luego luego envia por el socket 1 byte con la jugada
    * col|fil
    */
    void enviarJugada(Socket& socket, char& tipo_accion, char& col, char& fil);

    /*
    * Recibe mediante el socket 1 byte con la jugada
    */
    void recvJugada(Socket& socket, char& col, char& fil);

    /*
    * Destructor
    */
    ~Protocolo();
};

#endif
