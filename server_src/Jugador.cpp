#include "Jugador.h"
#include <string>
#include <utility>

#define VACIO ' '

Jugador::Jugador(Socket player_sock, MonitorPartidas& monitor):
                socketJugador(std::move(player_sock)),
                monitorPartidas(monitor), estaCorriendo(true){
  partidaActual = NULL;
  tipoJugador = VACIO;
}

bool Jugador::crear_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socketJugador, nombre);

  partidaActual = monitorPartidas.agregarPartidaSiNoExiste(nombre);
  tipoJugador = JUGADOR_O;
  return true;
}

bool Jugador::unirse_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socketJugador, nombre);

  partidaActual = monitorPartidas.buscarPartidaSiExiste(nombre);
  tipoJugador = JUGADOR_X;
  return true;
}

void Jugador::listar_partidas(Protocolo& protocolo) {
  std::string lista = monitorPartidas.listaPartidas();
  protocolo.enviarMensaje(socketJugador, lista);
}

void Jugador::entrarAPartida(Protocolo& protocolo){
  bool en_partida = false;
  char tipo_accion;
  while (!en_partida){
    protocolo.recvTipoAccion(socketJugador, tipo_accion);

    if (tipo_accion == CODIGO_LISTAR){
      listar_partidas(protocolo);
    }else if (tipo_accion == CODIGO_CREAR){
      en_partida = crear_partida(protocolo);
    }else if (tipo_accion == CODIGO_UNIRSE){
      en_partida = unirse_partida(protocolo);
    }
  }
}

void Jugador::jugarPartida(Protocolo& protocolo){
  std::string tablero;
  tablero = partidaActual->obtenerTablero(tipoJugador);

  while (partidaActual->enJuego() == true){
    protocolo.enviarMensaje(socketJugador, tablero);

    char tipo_accion;
    char col, fil;

    protocolo.recvTipoAccion(socketJugador, tipo_accion);
    protocolo.recvJugada(socketJugador, col, fil);

    partidaActual->jugar(tipoJugador, col, fil);
    tablero = partidaActual->obtenerTablero(tipoJugador);
  }

  protocolo.enviarMensaje(socketJugador, tablero);
}

void Jugador::run(){
  Protocolo protocolo;
  try{
    entrarAPartida(protocolo);
    jugarPartida(protocolo);
  }catch(const ExcepcionSocket& e){
    stop();
  }catch(const ExcepcionServer& e){
    stop();
  }
}

void Jugador::stop(){
  estaCorriendo = false;
  socketJugador.shutdown();
  socketJugador.close();
}

bool Jugador::corriendo() const{
  return estaCorriendo;
}

Jugador::~Jugador(){
  socketJugador.close();
}
