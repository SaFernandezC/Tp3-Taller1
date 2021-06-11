#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <Socket.h>
#include <string>

class Protocol{

  private:
    Socket client_socket;

  public:
    Protocol(const std::string& host, const std::string& port);

    void run(){}

    Protocol(Protocol&& other);
    Protocol& operator=(Protocol&& other);

    Protocol(const Protocol&)=delete;
    Protocol& operator=(const Protocol&)=delete;

    ~Protocol();

};

#endif
