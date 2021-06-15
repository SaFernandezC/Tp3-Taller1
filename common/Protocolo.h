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
    Protocolo();

    void recvTipoAccion(Socket& socket, char& tipo_accion);

    void enviarJugarUnirse(Socket& socket, const char& codigoAccion,
                          std::string& nombre);
    void enviarListar(Socket& socket, const char& codigoListar);

    void enviarMensaje(Socket& socket, const std::string& mensaje);
    void recvMensaje(Socket& socket, std::string& mensaje);

    void enviarJugada(Socket& socket, char& tipo_accion, char& col, char& fil);
    void recvJugada(Socket& socket, char& col, char& fil);

    ~Protocolo();
};

#endif
