#include <iostream>
#include "Listener.h"


int main(int argc, char const *argv[]) {

  if (argc != 2) {
    std::cout << "Para ejecutar --> ./server <port>" << std::endl;
    return -1;
  }

  std::string port(argv[1]);

  Listener listener(port);
  listener.start();


  std::string command = "";
  std::cin >> command;
  while (command.compare("q") != 0) {
    std::cout << "Comando invalido" << std::endl;
    std::cin >> command;
  }

  listener.stop();
  return 0;
}
