#ifndef _SOCKET_H
#define _SOCKET_H

#include <iostream>
#include <string>

class Socket{

  private:
    int fd;

    //Creo un socket con un file descriptor (la uso en accept)
    Socket(int fd);

  public:
    Socket();

    void connect(const std::string& host,const std::string& service);

    int bind(const std::string& port);

    int listen();

    Socket accept() const;

    void close();

    void shutdown();

    int send_msg(const char* buf, const int& size);
    int recv_msg(char* buf, const int& size);

    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    Socket(const Socket&); //BORRAR ESTO SI O SI
    Socket& operator=(const Socket&);

    ~Socket();



};

#endif
