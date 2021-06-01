#ifndef _SOCKET_H
#define _SOCKET_H

#include <string>

class Socket{

  private:
    int fd;

  public:

    Socket();

    void connect();

    void accept();

    int bind(const std::string& port);
    int listen();

    void close();

    int send_msg();
    int recv_msg();

    ~Socket();



};

#endif
