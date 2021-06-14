#include "Cliente.h"

Cliente::Cliente(const std::string& host, const std::string& port){
  try{
    client_socket.connect(host, port);
    conectado = true;
  } catch(std::exception& e){ //Ver si cambio exception por socketException
    std::cout << e.what() << std::endl; //Cambiar por un Syslog
  }
}

void Cliente::conectarAPartida(Protocolo& protocolo, Analizador& analizador){
  bool conectado = false;
  std::string jugada;

  while(!conectado){
    std::getline(std::cin, jugada);
    char accion = analizador.obtenerAccion(jugada);

    if(accion == CODIGO_NO_VALIDO){
      std::cout << "Accion no permitida" << '\n';
    } else {
      protocolo.enviarTipoAccion(client_socket, accion);
    }

    if(accion == CODIGO_CREAR || accion == CODIGO_UNIRSE){
        std::string nombre = analizador.obtenerNombre(jugada, 6); //Catchear excepcion
        protocolo.enviarMensaje(client_socket, nombre);
        conectado = true;
    } else if (accion == CODIGO_LISTAR){
      std::string lista;
      protocolo.recvMensaje(client_socket, lista);
      std::cout << lista << '\n';
    }
  }
}

void Cliente::jugar(Protocolo& protocolo, Analizador& analizador){

  std::string jugada;
  std::string tablero;
  bool jugando = true;

  protocolo.recvMensaje(client_socket, tablero);
  std::cout << tablero;

  while (jugando){
    std::getline(std::cin, jugada);

    char accion = analizador.obtenerAccion(jugada);
    if (accion != CODIGO_JUGAR){
      std::cout << "Accion no permitida" << '\n';
    }

    if (accion == CODIGO_JUGAR) {
      protocolo.enviarTipoAccion(client_socket, accion);

      char fila, col;
      analizador.obtenerFilaYCol(jugada, fila, col);
      protocolo.enviarJugada(client_socket, fila, col);

      protocolo.recvMensaje(client_socket, tablero);
      std::cout << tablero;

      if(analizador.partidaFinalizada(tablero)){
        jugando = false;
      }
    }
  }
}

void Cliente::run(){
  Analizador analizador;
  Protocolo protocolo;

  conectarAPartida(protocolo, analizador);
  
  jugar(protocolo, analizador);
}



Cliente::~Cliente(){
  client_socket.shutdown();
  client_socket.close();
}
