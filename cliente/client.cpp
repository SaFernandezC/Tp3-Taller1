#include <iostream>

#include "Socket.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cout << "Para ejecutar --> ./client <host> <port>" << std::endl;
    return -1;
  }

  std::string host(argv[1]);
  std::string port(argv[2]);


  Socket client;


  client.connect(host, port);

  client.shutdown();
  client.close();
  return 0;
}
