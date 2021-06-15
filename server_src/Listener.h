#ifndef _LISTENER_H
#define _LISTENER_H

#include "Thread.h"
#include <atomic>
#include <string>
#include "../common_src/Socket.h"
#include "Organizador.h"

class Listener: public Thread{
  private:
    Socket aceptador;
    std::atomic<bool> seguirAceptando;
    Organizador organizador;

  public:
    explicit Listener(const std::string& port);

    /*
    * Mientras el server indique que se sigue aceptando
    * acepta sockets clientes y se los pasa al organizador
    *con el metodo agregarJugador.
    */
    virtual void run() override;

    /*
    * Hace shutdown del socket accepter y cambia la condicion
    * del loop de aceptar para no aceptar mas clientes.
    */
    void stop();

    ~Listener();
};

#endif
