#include "Cliente.h"

Cliente::Cliente(const std::string& host, const std::string& port){
  client_socket.connect(host, port);
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

    std::string nombre;

    if(accion == CODIGO_CREAR){
        nombre = analizador.obtenerNombre(jugada, 6); //Catchear excepcion
        protocolo.enviarMensaje(client_socket, nombre);
        conectado = true;
    } else if (accion == CODIGO_UNIRSE) {
      nombre = analizador.obtenerNombre(jugada, 7); //Catchear excepcion
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

      char fil, col; //Agregar chequeo para validar
      analizador.obtenerFilaYCol(jugada, col, fil);
      protocolo.enviarJugada(client_socket, col, fil);

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
