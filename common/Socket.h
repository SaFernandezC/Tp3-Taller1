#ifndef _SOCKET_H
#define _SOCKET_H

#include <iostream>
#include <string>
#include "SocketException.h"

class Socket{

  private:
    int fd;

  public:
    /*
    * Constructor
    */
    Socket();

    /*
    * Constructor
    */
    void connect(const std::string& host,const std::string& service);

    /*
    * Constructor
    */
    void bind(const std::string& port);

    /*
    * Constructor
    */
    void listen();

    /*
    * Constructor
    */
    Socket accept() const;

    /*
    * Constructor
    */
    void close();

    /*
    * Constructor
    */
    void shutdown();

    /*
    * Constructor
    */
    int sendMsg(const char* buf, const int& size);

    /*
    * Constructor
    */
    int recvMsg(char* buf, const int& size);

    /*
    * Constructor
    */
    Socket(Socket&& other);

    /*
    * Constructor
    */
    Socket& operator=(Socket&& other);

    /*
    * Destructor
    */
    ~Socket();

  private:
    /*
    * Constructor, asigna al socket el fd recibido
    * como parametro
    */
    Socket(int fd);
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;



};

#endif
