#include <iostream>
#include "Server.h"


int main(int argc, char const *argv[]) {

  if (argc != 2) {
    std::cout << "Para ejecutar --> ./server <port>" << std::endl;
    return -1;
  }

  std::string port(argv[1]);

  Server server(port);

  return 0;
}
