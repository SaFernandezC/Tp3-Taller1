#include "Socket.h"

#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> //Close la utiliza
#include <arpa/inet.h> // inet_ntop -> Convierte addr de bin a text

Socket::Socket(){}

int Socket::bind(const std::string& port){

  int status;

  struct addrinfo hints, *server_info;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, port.c_str(), &hints, &server_info);
  if (status != 0){
    return -1;
  }

  sock_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  if (sock_fd  == -1){
    freeaddrinfo(server_info);
    return -1;
  }

  int val = 1;
  status = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  if (status == -1){
    freeaddrinfo(server_info);
    return status;
  }

  status = ::bind(sock_fd, server_info->ai_addr, server_info->ai_addrlen);
  if (status == -1){
    ::close(sock_fd);
    freeaddrinfo(server_info);
    return status;
  }

  freeaddrinfo(server_info);


  return 0;
}

int Socket::listen(){

  int status = ::listen(sock_fd, 10); //Ver ese 10
  if (status == -1){
    ::close(sock_fd);
  }
  return status;
}

int Socket::accept(int fd, struct sockaddr* addr, socklen_t* addr_len){
  sock_fd = accept(fd, addr, addr_len);
  if (sock_fd == ERROR){
    return ERROR; //Excepcion
  }
  return OK;
}

Socket::~Socket(){}
