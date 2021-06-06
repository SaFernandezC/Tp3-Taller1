#ifndef _ACCEPTER_H
#define _ACCEPTER_H

#include "Thread.h"
#include "Player.h"
#include "Socket.h"
#include <vector>

class Accepter: public Thread{

  private:
    // std::vector<Player>& jugadores;
    Socket& server_socket;
    bool keep_accepting;


  public:

    Accepter(Socket& server_sock);

    virtual void run() override;

    void stop();

    ~Accepter();



};

#endif
