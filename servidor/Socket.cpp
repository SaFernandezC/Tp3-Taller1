#include "Socket.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> //Close la utiliza
#include <arpa/inet.h> // inet_ntop -> Convierte addr de bin a text

#include "SocketException.h"


Socket::Socket(){}

Socket::Socket(int fd):fd(fd){}

/*-----------------------------------------------------------*/

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
  std::cout << "Se acepto un cliente con el fd: " << accepted_fd << std::endl;
  Socket accepted(accepted_fd);
  return accepted;
}

void Socket::connect(const std::string& host,const std::string& service){
  struct addrinfo hints, *server_info;

  memset(&hints, 0, sizeof(struct addrinfo));

  int result = getaddrinfo(host.c_str(), service.c_str(), &hints, &server_info);
  if (result != 0){
    return;
  }

  fd = socket(server_info->ai_family, server_info->ai_socktype,
    server_info->ai_protocol);
    if (fd == -1){
      freeaddrinfo(server_info);
      return;
    }

    int status = ::connect(fd, server_info->ai_addr, server_info->ai_addrlen);
    if (status == -1){
      freeaddrinfo(server_info);
      return;
    }

    freeaddrinfo(server_info);
    std::cout << "Me conecte a " << host << " en el puerto " << service << '\n';
    return;
}


/*-----------------------------------------------------------*/

int Socket::send_msg(const char* buf, const int& size){
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
     throw SocketException("Error al enviar mensaje de %i bytes\n", size, __LINE__);
  }
}

int Socket::recv_msg(char* buf, const int& size){
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
    throw SocketException("Error al recibir mensaje de %i bytes\n", size, __LINE__);
  }
}

/*-----------------------------------------------------------*/

void Socket::shutdown(){
  ::shutdown(fd, SHUT_RDWR);
}

void Socket::close(){
  ::close(fd);
}

Socket::Socket(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
  std::cout << "Constructor por moviemiento Socket" << '\n';
}

Socket& Socket::operator=(Socket&& other){
  if(this != &other){
    this->fd = other.fd;
    other.fd = -1;
  }
  std::cout << "Asigno por moviemiento socket" << '\n';
  return *this;
}

Socket::Socket(const Socket&){
  std::cout << "Constructor por copia Socket" << '\n';
}
Socket& Socket::operator=(const Socket&){
  std::cout << "Asigno por copia socket" << '\n';
  return *this;
}

Socket::~Socket(){
  //Close? necesito if(fd == valid ) => close?
}
