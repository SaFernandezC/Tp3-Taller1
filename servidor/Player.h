#ifndef _PLAYER_H
#define _PLAYER_H

#include "Socket.h"
#include "Thread.h"

class Player: public Thread{

  private:
    Socket player_socket;
    //Deberia tener las partidas o el monitor quizas -> Creo que mejor una sola partida

  public:

    Player(Socket player_sock);

    virtual void run() override;

    ~Player();



};

#endif
