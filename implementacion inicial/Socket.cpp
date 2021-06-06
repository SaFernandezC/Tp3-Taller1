#include "Socket.h"

#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> //Close la utiliza
#include <arpa/inet.h> // inet_ntop -> Convierte addr de bin a text

Socket::Socket(){}

Socket::Socket(int fd):fd(fd){}

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

  fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  if (fd  == -1){
    freeaddrinfo(server_info);
    return -1;
  }

  int val = 1;
  status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  if (status == -1){
    freeaddrinfo(server_info);
    return status;
  }

  status = ::bind(fd, server_info->ai_addr, server_info->ai_addrlen);
  if (status == -1){
    ::close(fd);
    freeaddrinfo(server_info);
    return status;
  }

  freeaddrinfo(server_info);


  return 0;
}

int Socket::listen(){

  int status = ::listen(fd, 10); //Ver ese 10
  if (status == -1){
    ::close(fd);
  }
  return status;
}


Socket Socket::accept() const{
  int accepted_fd = ::accept(fd, NULL, NULL);
  if (accepted_fd == -1) {
    throw SocketException("Error al intentar aceptar un cliente -> fd: %d\n", accepted_fd, __LINE__);
  }
  std::cout << "se acepto un cliente" << std::endl;
  Socket accepted(accepted_fd);
  return accepted;
}


Socket::Socket(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
}

Socket& Socket::operator=(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
  return *this;
}

Socket::~Socket(){
  //Close? necesito if(fd == valid ) => close?
}
