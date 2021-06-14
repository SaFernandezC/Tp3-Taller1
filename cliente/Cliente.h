#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../common/Socket.h"
#include "../common/Protocolo.h"
#include "Analizador.h"
#include <string>

class Cliente{

  private:
    Socket client_socket;
    bool conectado;

  public:
    Cliente(const std::string& host, const std::string& port);

    void run();

    Cliente(Cliente&& other);
    Cliente& operator=(Cliente&& other);

    Cliente(const Cliente&)=delete;
    Cliente& operator=(const Cliente&)=delete;

    ~Cliente();

  private:
    void conectarAPartida(Protocolo& protocolo, Analizador& analizador);
    void jugar(Protocolo& protocolo, Analizador& analizador);
};

#endif
