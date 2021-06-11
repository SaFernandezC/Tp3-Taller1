#include <iostream>

#include "Protocol.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cout << "Para ejecutar --> ./client <host> <port>" << std::endl;
    return -1;
  }

  std::string host(argv[1]);
  std::string port(argv[2]);

  Protocol protocolo(host, port);

  
  return 0;
}
