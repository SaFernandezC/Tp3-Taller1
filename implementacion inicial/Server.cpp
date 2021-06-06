#include "Server.h"

Server::Server(const std::string& port):port(port){
  aceptador = new Accepter(server_socket);
}


void Server::run(){

  server_socket.bind(port);
  server_socket.listen();

  aceptador->start();

  std::string command = "";
  std::cin >> command;
  while (command.compare("q") != 0) {
    std::cout << "Comando invalido" << std::endl;
    std::cin >> command;
  }



  aceptador->stop();
  aceptador->join();

}

Server::~Server(){
  delete aceptador;
}
