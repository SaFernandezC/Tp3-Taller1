#ifndef _LISTENER_H
#define _LISTENER_H

#include "Thread.h"
#include <atomic>
#include "../common/Socket.h"
#include "Organizador.h"

class Listener: public Thread{

  private:
    Socket accepter;
    std::atomic<bool> seguirAceptando;
    Organizador organizador;


  public:

    Listener(std::string& port);

    virtual void run() override;

    void stop();

    ~Listener();

};

#endif
