#ifndef _JUGADOR_H
#define _JUGADOR_H

#include "Socket.h"
#include "Thread.h"

class Jugador: public Thread{

  private:
    Socket player_socket;
    //Deberia tener las partidas o el monitor quizas -> Creo que mejor una sola partida

  public:

    Jugador(Socket player_sock);

    virtual void run() override;

    ~Jugador();



};

#endif
