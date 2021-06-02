#include "Accepter.h"


Accepter::Accepter(std::vector<Player>& players, Socket& server_sock):jugadores(players), server_socket(server_sock){
}

void Accepter::run(){

  // while (entra un q por cin) {
  //   /* code */
  // }


  while(seguir_aceptando){

  char addr_buf[INET_ADDRSTRLEN];
  struct sockaddr_in address;
  int status = 0;
  socklen_t addr_len = (socklen_t) sizeof(address);

  status = socket_accept(skt, self->fd, (struct sockaddr*)&address, &addr_len);
  if (status == ERROR){
    return ERROR;
  }

  inet_ntop(AF_INET, &(address.sin_addr), addr_buf, INET_ADDRSTRLEN);
  return OK;


    Player client = server_socket.accept();
    jugadores.push_back(std::move(client));
  }


}

Accepter::~Accepter(){

}
