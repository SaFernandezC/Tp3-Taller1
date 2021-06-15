#include "Protocolo.h"

#include <arpa/inet.h>
#include <vector>
#include <string>

#define SIZE_MSG_LEN 2
#define DIFERENCIA 49
#define LONG_MSG_ACCION 1
#define LONG_MSG_JUGADA 1
#define PLANTILLA 0x0F

Protocolo::Protocolo(){}

void Protocolo::enviarMensaje(Socket& socket, const std::string& mensaje){
  uint16_t largoMsg = htons(mensaje.length());
  socket.sendMsg((char*)&largoMsg, SIZE_MSG_LEN);
  socket.sendMsg(mensaje.c_str(), mensaje.length());
}

void Protocolo::recvMensaje(Socket& socket, std::string& mensaje){
  uint16_t largoMsg;
  socket.recvMsg((char*)&largoMsg, SIZE_MSG_LEN);
  largoMsg = ntohs(largoMsg);

  std::vector<char> temp(largoMsg+1);
  socket.recvMsg(&temp[0], largoMsg);
  temp[largoMsg] = '\0';
  mensaje = &temp[0];
}

void Protocolo::enviarCrearUnirse(Socket& socket,
              const char& codigoAccion, std::string& nombre) {
  socket.sendMsg((char*)&codigoAccion, LONG_MSG_ACCION);
  uint16_t largoMsg = htons(nombre.length());
  socket.sendMsg((char*)&largoMsg, SIZE_MSG_LEN);
  socket.sendMsg(nombre.c_str(), nombre.length());
}

void Protocolo::enviarListar(Socket& socket, const char& codigoListar){
  socket.sendMsg((char*)&codigoListar, LONG_MSG_ACCION);
}

void Protocolo::recvTipoAccion(Socket& socket, char& tipoAccion){
  socket.recvMsg((char*)&tipoAccion, LONG_MSG_ACCION);
}

void Protocolo::recvJugada(Socket& socket, char& col, char& fil){
  char jugada;
  socket.recvMsg(&jugada, LONG_MSG_JUGADA);

  fil = (jugada & PLANTILLA);
  col = (jugada >> 4);
}

void Protocolo::enviarJugada(Socket& socket, char& tipoAccion,
                char& col, char& fil){
  fil = fil - DIFERENCIA;
  col = col - DIFERENCIA;
  col = col << 4; //desplazo 4 bits a izq

  char mensaje = col | fil;
  socket.sendMsg((char*)&tipoAccion, LONG_MSG_ACCION);
  socket.sendMsg(&mensaje, LONG_MSG_JUGADA);
}

Protocolo::~Protocolo(){}
