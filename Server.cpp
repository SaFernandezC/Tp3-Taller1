#include "Server.h"

#include <string.h> //memset

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> //Close la utiliza
#include <arpa/inet.h> // inet_ntop -> Convierte addr de bin a text

Server::Server(const std::string& port):port(port){
  aceptador = new Accepter(jugadores, server_socket);
}

// int Server::bind(){
//   int status;
//
//   struct addrinfo hints, *server_info;
//   memset(&hints, 0, sizeof(struct addrinfo));
//   hints.ai_family = AF_INET;
//   hints.ai_socktype = SOCK_STREAM;
//   hints.ai_flags = AI_PASSIVE;
//
//   status = getaddrinfo(NULL, port.c_str(), &hints, &server_info);
//   if (status != 0){
//     return -1;
//   }
//
//   server_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
//   if (fd  == -1){
//     freeaddrinfo(server_info);
//     return -1;
//   }
//
//   int val = 1;
//   status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
//   if (status == -1){
//     freeaddrinfo(server_info);
//     return status;
//   }
//
//   status = ::bind(fd, server_info->ai_addr, server_info->ai_addrlen);
//   if (status == -1){
//     ::close(fd);
//     freeaddrinfo(server_info);
//     return status;
//   }
//
//   freeaddrinfo(server_info);
//
//
//   return 0;
// }
//
// int Server::listen(){
//
// }

void Server::run(){

  server_socket.bind(port);
  server_socket.listen();
  // bind();
  // listen();

  // aceptador->start();

}

Server::~Server(){

}
