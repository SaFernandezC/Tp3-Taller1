#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H

#include "Socket.h"

#define CODIGO_JUGAR 0x70
#define CODIGO_LISTAR 0x6C
#define CODIGO_CREAR 0x6E
#define CODIGO_UNIRSE 0x6A

class Protocolo{

  private:

  public:
    Protocolo();

    void enviarTipoAccion(Socket& socket, const char& tipo_accion);
    void recvTipoAccion(Socket& socket, char& tipo_accion);

    void enviarMensaje(Socket& socket, const std::string& mensaje);
    void recvMensaje(Socket& socket, std::string& mensaje);

    void enviarJugada(Socket& socket, char& fil, char& col);
    void recvJugada(Socket& socket, char& fil, char& col);

    ~Protocolo();

};

#endif
