#include "Cliente.h"
#include <string>

#define POS_CREAR 6
#define POS_UNIRSE 7

Cliente::Cliente(const std::string& host, const std::string& port){
  client_socket.connect(host, port);
}

void Cliente::conectarAPartida(Protocolo& protocolo, Analizador& analizador){
  bool conectado = false;
  std::string jugada;

  while (!conectado){
    try{
      std::getline(std::cin, jugada);
      char accion = analizador.obtenerAccion(jugada);

      if (accion == CODIGO_NO_VALIDO){
        std::cout << "Accion no permitida" << '\n';
      }

      std::string nombre;

      if (accion == CODIGO_CREAR){
        nombre = analizador.obtenerNombre(jugada, POS_CREAR);
        protocolo.enviarCrearUnirse(client_socket, accion, nombre);
        conectado = true;
      } else if (accion == CODIGO_UNIRSE) {
        nombre = analizador.obtenerNombre(jugada, POS_UNIRSE);
        protocolo.enviarCrearUnirse(client_socket, accion, nombre);
        conectado = true;
      } else if (accion == CODIGO_LISTAR){
        std::string lista;
        protocolo.enviarListar(client_socket, accion);
        protocolo.recvMensaje(client_socket, lista);
        std::cout << lista;
      }
    }catch(const ExcepcionSocket& e){
      throw;
    }catch(const ExcepcionCliente& e){
      std::cout << e.what();
      conectado = false;
    }
  }
}

void Cliente::jugar(Protocolo& protocolo, Analizador& analizador){
  std::string jugada;
  std::string tablero;
  bool jugando = true;

  try{
    protocolo.recvMensaje(client_socket, tablero);
    std::cout << tablero;
  }catch(const ExcepcionSocket& e){
    throw;
  }

  while (jugando){
    try{
      std::getline(std::cin, jugada);

      char accion = analizador.obtenerAccion(jugada);
      if (accion != CODIGO_JUGAR){
        std::cout << "Accion no permitida" << '\n';
      }

      if (accion == CODIGO_JUGAR) {
        char fil, col;
        analizador.obtenerFilaYCol(jugada, col, fil);
        analizador.verificarIngreso(col, fil);
        protocolo.enviarJugada(client_socket, accion, col, fil);

        protocolo.recvMensaje(client_socket, tablero);
        std::cout << tablero;

        if (analizador.partidaFinalizada(tablero)){
          jugando = false;
        }
      }
    }catch(const ExcepcionSocket& e){
      throw;
    }catch(const ExcepcionCliente& e){
      std::cout << e.what();
    }
  }
}

void Cliente::run(){
  Analizador analizador;
  Protocolo protocolo;

  try{
    conectarAPartida(protocolo, analizador);
    jugar(protocolo, analizador);
  } catch(const ExcepcionSocket& e){
    throw;
  }
}

Cliente::~Cliente(){
  client_socket.shutdown();
  client_socket.close();
}
