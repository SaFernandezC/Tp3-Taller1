#ifndef _ACCEPTER_H
#define _ACCEPTER_H

#include "Thread.h"
#include "Player.h"
#include "Socket.h"
#include <vector>

class Accepter: public Thread{

  private:
    std::vector<Player>& jugadores;
    Socket& server_socket;


  public:

    Accepter(std::vector<Player>& players, Socket& server_sock);

    virtual void run() override;

    ~Accepter();



};

#endif
