#include "Protocolo.h"

#include <arpa/inet.h> // Para htons y y ntohs
#include <vector>

#define SIZE_MSG_LEN 2
#define DIFERENCIA 49
#define PLANTILLA 0x0F

Protocolo::Protocolo(){}

void Protocolo::enviarMensaje(Socket& socket, const std::string& mensaje){
  uint16_t largo_msg = htons(mensaje.length());
  socket.sendMsg((char*)&largo_msg, SIZE_MSG_LEN); //Ver si cambio el int por una exception

  // std::cout << "Envio el largo del mensaje de la partida: "<< mensaje.length() << '\n';

  socket.sendMsg(mensaje.c_str(), mensaje.length()); //Ver si cambio el int por una exception
  // std::cout << "Envio el mensaje de la partida: "<< mensaje << '\n';
}

void Protocolo::recvMensaje(Socket& socket, std::string& mensaje){

  uint16_t largo_msg;
  socket.recvMsg((char*)&largo_msg, SIZE_MSG_LEN);
  largo_msg = ntohs(largo_msg);

  // std::cout << "Recibo el largo del mensaje de la partida: "<< largo_msg << '\n';

  std::vector<char> temp(largo_msg+1);

  socket.recvMsg(&temp[0], largo_msg);

  temp[largo_msg] = '\0';
  mensaje = &temp[0];
  // std::cout << "Recivo el mensaje de la partida: "<< mensaje << '\n';
}

void Protocolo::enviarTipoAccion(Socket& socket, const char& tipo_accion){
  socket.sendMsg((char*)&tipo_accion, 1);
  // std::cout << "Envio Tipo de accion: " << tipo_accion<< '\n';
}

void Protocolo::recvTipoAccion(Socket& socket, char& tipo_accion){
  socket.recvMsg((char*)&tipo_accion, 1);
  // std::cout << "Recivo Tipo de accion: " << tipo_accion<< '\n';
}

void Protocolo::recvJugada(Socket& socket, char& fil, char& col){
  char jugada;
  socket.recvMsg(&jugada, 1);

  fil = (jugada & PLANTILLA);
  col = (jugada >> 4);



}

void Protocolo::enviarJugada(Socket& socket, char& fil, char& col){

  fil = fil - DIFERENCIA;
  col = col - DIFERENCIA;
  col = col << 4; //desplazo 4 bits a izq

  char mensaje = col | fil;

  socket.sendMsg(&mensaje, 1);
}


Protocolo::~Protocolo(){}
