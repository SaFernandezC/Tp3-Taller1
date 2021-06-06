#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <vector>
#include "string"
#include "Accepter.h"
#include "Socket.h"
#include "Player.h"

class Server{

  private:
    Accepter* aceptador;
    Socket server_socket;
    std::vector<Player> jugadores;
    std::string port;

  public:

    Server(const std::string& port);

    int bind();
    int listen();

    void run();

    ~Server();



};

#endif
