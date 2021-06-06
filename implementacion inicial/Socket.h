#ifndef _SOCKET_H
#define _SOCKET_H

#include <iostream>
#include <string>
#include "SocketException.h"

class Socket{

  private:
    int fd;

    //Creo un socket con un file descriptor (la uso en accept)
    Socket(int fd);

  public:

    Socket();

    void connect();

    int bind(const std::string& port);

    int listen();

    Socket accept() const;

    void close();

    int send_msg();
    int recv_msg();

    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    ~Socket();



};

#endif
