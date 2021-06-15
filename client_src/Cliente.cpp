#include "Cliente.h"
#include <string>

#define POS_CREAR 6
#define POS_UNIRSE 7

Cliente::Cliente(const std::string& host, const std::string& port){
  socketCliente.connect(host, port);
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
        protocolo.enviarCrearUnirse(socketCliente, accion, nombre);
        conectado = true;
      } else if (accion == CODIGO_UNIRSE) {
        nombre = analizador.obtenerNombre(jugada, POS_UNIRSE);
        protocolo.enviarCrearUnirse(socketCliente, accion, nombre);
        conectado = true;
      } else if (accion == CODIGO_LISTAR){
        std::string lista;
        protocolo.enviarListar(socketCliente, accion);
        protocolo.recvMensaje(socketCliente, lista);
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
    protocolo.recvMensaje(socketCliente, tablero);
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
        protocolo.enviarJugada(socketCliente, accion, col, fil);

        protocolo.recvMensaje(socketCliente, tablero);
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
  socketCliente.shutdown();
  socketCliente.close();
}
