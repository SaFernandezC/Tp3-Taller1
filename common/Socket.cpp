#include "Socket.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> //Close la utiliza
#include <arpa/inet.h> // inet_ntop -> Convierte addr de bin a text

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
  if (status != 0){
    throw SocketException("Error en la funcion getaddrinfo. [%s]:%i\n", __FILE__,__LINE__);
  }

  fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  if (fd  == -1){
    freeaddrinfo(server_info);
    throw SocketException("Error en la funcion socket. [%s]:%i\n", __FILE__,__LINE__);
  }

  int val = 1;
  status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  if (status == -1){
    freeaddrinfo(server_info);
    throw SocketException("Error en la funcion setsockopt previo al bind. [%s]:%i\n", __FILE__,__LINE__);
  }

  status = ::bind(fd, server_info->ai_addr, server_info->ai_addrlen);
  freeaddrinfo(server_info);

  if (status == -1){
    ::close(fd);
    throw SocketException("Error en la funcion bind. [%s]:%i\n", __FILE__,__LINE__);
  }
}

void Socket::listen(){
  int status = ::listen(fd, 10); //Ver ese 10
  if (status == -1){
    ::close(fd);
    throw SocketException("Error al crear la cola de espera. [%s]:%i\n", __FILE__,__LINE__);
  }
}

Socket Socket::accept() const{
  int accepted_fd = ::accept(fd, NULL, NULL);
  if(errno == EINVAL){
    throw SocketException("Mientras se esperaba para hacer un accept se hizo un shutdown del socket. [%s]:%i\n",__FILE__,__LINE__);
  }
  if (accepted_fd == -1) {
    throw SocketException("Error al intentar aceptar un cliente. [%s]:%i\n",__FILE__,__LINE__);
  }
  Socket accepted(accepted_fd);
  return accepted;
}

void Socket::connect(const std::string& host,const std::string& service){
  struct addrinfo hints, *server_info;
  memset(&hints, 0, sizeof(struct addrinfo));

  int result = getaddrinfo(host.c_str(), service.c_str(), &hints, &server_info);
  if (result != 0){
    throw SocketException("Error en la funcion getaddrinfo\n", __FILE__,__LINE__);
  }

  bool conectado = false;
  int status;
  addrinfo* ptr;

  for (ptr = server_info; ptr != NULL && conectado == false; ptr = ptr->ai_next) {
    fd = socket(server_info->ai_family, server_info->ai_socktype,server_info->ai_protocol);
    if (fd != -1){
      status = ::connect(fd, server_info->ai_addr, server_info->ai_addrlen);
      if(status == -1){
        ::close(fd);
      } else{
        conectado = true;
      }
    }
  }

  freeaddrinfo(server_info);
  if(!conectado){
    fd = -1;
    throw SocketException("Error al intentar conectarse al servidor\n", __FILE__,__LINE__);
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
     throw SocketException("Error al enviar mensaje de %i bytes. [%s]:%i\n", size, __FILE__, __LINE__);
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
    throw SocketException("Error al recibir mensaje de %i bytes. [%s]:%i\n", size, __FILE__, __LINE__);
  }
}

/*-----------------------------------------------------------*/

void Socket::shutdown(){
  if (fd != -1){
    ::shutdown(fd, SHUT_RDWR);
  }
}

void Socket::close(){
  if (fd != -1){
    ::close(fd);
    fd = -1;
  }
}

Socket::Socket(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
  // std::cout << "Constructor por moviemiento Socket" << '\n';
}

Socket& Socket::operator=(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
  // std::cout << "Asigno por moviemiento socket" << '\n';
  return *this;
}

Socket::~Socket(){
  if(fd != -1){
    ::close(fd);
  }
}
