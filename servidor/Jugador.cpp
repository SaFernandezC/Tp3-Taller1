#include "Jugador.h"

Jugador::Jugador(Socket player_sock, MonitorPartidas& monitor):socket_jugador(std::move(player_sock)),
                monitor_partidas(monitor), estaCorriendo(true){
}

bool Jugador::crear_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socket_jugador, nombre);

  if(monitor_partidas.existePartida(nombre)){
    return false;
  }

  partidaActual = monitor_partidas.agregarPartida(nombre);
  tipoJugador = JUGADOR_X;
  return true;
}

bool Jugador::unirse_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socket_jugador, nombre);

  if(monitor_partidas.existePartida(nombre) == false){
    return false;
  }

  partidaActual = monitor_partidas.buscarPartida(nombre);
  tipoJugador = JUGADOR_O;
  return true;
}

void Jugador::listar_partidas(Protocolo& protocolo) {
  std::string lista = monitor_partidas.listaPartidas();
  protocolo.enviarMensaje(socket_jugador, lista);
}

void Jugador::run(){

  Protocolo protocolo;
  bool en_partida = false;

  while(!en_partida){
    char tipo_accion;
    protocolo.recvTipoAccion(socket_jugador, tipo_accion);

    if (tipo_accion == CODIGO_LISTAR){
      listar_partidas(protocolo);
    }else if (tipo_accion == CODIGO_CREAR){
      en_partida = crear_partida(protocolo);
    }else if(tipo_accion == CODIGO_UNIRSE){
      en_partida = unirse_partida(protocolo);
    }
  }

  std::string tablero;
  tablero = partidaActual->obtenerTablero(tipoJugador);

  while(partidaActual->enJuego() == true){
    protocolo.enviarMensaje(socket_jugador, tablero);

    char tipo_accion;
    char col, fil;

    protocolo.recvTipoAccion(socket_jugador, tipo_accion); //PUEDE SER DIFERENTE DE CODIGO_JUGAR?
    protocolo.recvJugada(socket_jugador, col, fil);

    partidaActual->jugar(tipoJugador, col, fil);
    tablero = partidaActual->obtenerTablero(tipoJugador);
  }

  protocolo.enviarMensaje(socket_jugador, tablero);

  // monitor_partidas.eliminarPartida(partidaActual->obtenerNombre());
  stop();
}

void Jugador::stop(){
  estaCorriendo = false;
  socket_jugador.shutdown();
  socket_jugador.close();
}

bool Jugador::corriendo() const{
  return estaCorriendo;
}

Jugador::~Jugador(){
  socket_jugador.close();
}
