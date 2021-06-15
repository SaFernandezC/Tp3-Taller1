#include "Socket.h"
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define LONG_COLA 10
#define ERROR -1
#define NO_INIT -1
#define EXITO 0


Socket::Socket(){}

Socket::Socket(int fd):fd(fd){}

/*-----------------------------------------------------------*/

void Socket::bind(const std::string& port){
  int status;

  struct addrinfo hints, *server_info;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, port.c_str(), &hints, &server_info);
  if (status != EXITO){
    throw ExcepcionSocket("Error en la funcion getaddrinfo."
                " [%s]:%i\n", __FILE__,__LINE__);
  }

  bool conectado = false;
  addrinfo* ptr;
  int val = 1;

  for (ptr = server_info; ptr != NULL && conectado == false;
    ptr = ptr->ai_next) {
      fd = socket(server_info->ai_family, server_info->ai_socktype,
        server_info->ai_protocol);
        if (fd != ERROR){
          status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
          if (status != ERROR){
            status = ::bind(fd, server_info->ai_addr, server_info->ai_addrlen);
            if (status != ERROR){
              conectado = true;
            }
          }
        }
        if (conectado == false){
          ::close(fd);
        }
      }

      freeaddrinfo(server_info);
      if (!conectado){
        throw ExcepcionSocket("Error al crear aceptador en."
                " la funcion bind [%s]:%i\n", __FILE__,__LINE__);
      }
}

void Socket::listen(){
  int status = ::listen(fd, LONG_COLA);
  if (status == ERROR){
    ::close(fd);
    throw ExcepcionSocket("Error al crear la cola de espera."
                          " [%s]:%i\n", __FILE__,__LINE__);
  }
}

Socket Socket::accept() const{
  int accepted_fd = ::accept(fd, NULL, NULL);
  if (errno == EINVAL){
    throw ExcepcionSocket("Mientras se esperaba para hacer un accept se hizo"
      "un shutdown del socket. [%s]:%i\n",__FILE__,__LINE__);
  }
  if (accepted_fd == ERROR) {
    throw ExcepcionSocket("Error al intentar aceptar un cliente."
                          " [%s]:%i\n",__FILE__,__LINE__);
  }
  Socket accepted(accepted_fd);
  return accepted;
}

void Socket::connect(const std::string& host,const std::string& service){
  struct addrinfo hints, *server_info;
  memset(&hints, 0, sizeof(struct addrinfo));

  int result = getaddrinfo(host.c_str(), service.c_str(), &hints, &server_info);
  if (result != EXITO){
    throw ExcepcionSocket("Error en la funcion getaddrinfo."
                          " [%s]:%i\n", __FILE__,__LINE__);
  }

  bool conectado = false;
  int status;
  addrinfo* ptr;

  for (ptr = server_info; ptr != NULL && conectado == false;
      ptr = ptr->ai_next) {
    fd = socket(server_info->ai_family, server_info->ai_socktype,
                server_info->ai_protocol);
    if (fd != ERROR){
      status = ::connect(fd, server_info->ai_addr, server_info->ai_addrlen);
      if (status == ERROR){
        ::close(fd);
      } else{
        conectado = true;
      }
    }
  }

  freeaddrinfo(server_info);
  if (!conectado){
    fd = -1;
    throw ExcepcionSocket("Error al intentar conectarse al servidor."
                          " [%s]:%i\n", __FILE__,__LINE__);
  }
}


/*-----------------------------------------------------------*/

int Socket::sendMsg(const char* buf, const int& size){
  int sent = 0;
  bool valid_socket = true;

  while (sent < size && valid_socket) {
     int bytes = send(fd, &buf[sent], size-sent, MSG_NOSIGNAL);

     if (bytes == 0) {
        valid_socket = false;
     } else if (bytes == -1) {
        valid_socket = false;
     } else {
        sent += bytes;
     }
  }

  if (valid_socket) {
     return sent;
  } else {
     throw ExcepcionSocket("Error al enviar mensaje de %i bytes."
                          " [%s]:%i\n", size, __FILE__, __LINE__);
  }
}

int Socket::recvMsg(char* buf, const int& size){
  int received = 0;
  bool valid_socket = true;

  while (received < size && valid_socket) {
    int bytes = recv(fd, &buf[received], size-received, 0);

    if (bytes == 0) { // nos cerraron el socket :(
      valid_socket = false;
    } else if (bytes == -1) { // hubo un error >(
      valid_socket = false;
    } else {
      received += bytes;
    }
  }

  if (valid_socket) {
    return received;
  } else {
    throw ExcepcionSocket("Error al recibir mensaje de %i bytes."
                          " [%s]:%i\n", size, __FILE__, __LINE__);
  }
}

/*-----------------------------------------------------------*/

void Socket::shutdown(){
  if (fd != NO_INIT){
    ::shutdown(fd, SHUT_RDWR);
  }
}

void Socket::close(){
  if (fd != NO_INIT){
    ::close(fd);
    fd = NO_INIT;
  }
}

Socket::Socket(Socket&& other){
  if (this != &other){
    this->fd = other.fd;
    other.fd = NO_INIT;
  }
}

Socket& Socket::operator=(Socket&& other){
  if (this != &other){
    this->fd = other.fd;
    other.fd = NO_INIT;
  }
  return *this;
}

Socket::~Socket(){
  if (fd != NO_INIT){
    ::shutdown(fd, SHUT_RDWR);
    ::close(fd);
  }
}
