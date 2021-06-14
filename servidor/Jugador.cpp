#include "Jugador.h"

Jugador::Jugador(Socket player_sock, MonitorPartidas& monitor):socket_jugador(std::move(player_sock)),
                monitor_partidas(monitor), estaCorriendo(true){
}

bool Jugador::crear_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socket_jugador, nombre);

  try{
    partidaActual = monitor_partidas.agregarPartida(nombre);
  } catch(...){//Aca va la excepcion de nombre ya existente
    //Envio Mensaje de error
    std::cout << "La partida ya existe" << '\n';
    return false;
  }
  tipoJugador = JUGADOR_X;
  return true;
}

bool Jugador::unirse_partida(Protocolo& protocolo){
  std::string nombre;
  protocolo.recvMensaje(socket_jugador, nombre);

  try{
    partidaActual = monitor_partidas.buscarPartida(nombre); //Separar en existe y luego busco
  } catch(...){//Aca va la excepcion de nombre ya existente
    //Envio Mensaje de error
    std::cout << "No existe partida" << '\n';
    return false;
  }
  tipoJugador = JUGADOR_O;
  return true;
}

void Jugador::listar_partidas(Protocolo& protocolo) {
  std::string lista = monitor_partidas.listaPartidas();
  protocolo.enviarMensaje(socket_jugador, lista);
}

void Jugador::run(){

  Protocolo protocolo;
  // std::string nombrePartida;
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


  // while(partidaActual->enJuego() == true){
  //   std::string tablero = partidaActual->obtenerTablero();
  //   protocolo.enviarMensaje(socket_jugador, tablero);
  //
  //   char tipo_accion;
  //   char fil, col;
  //
  //   protocolo.recvTipoAccion(socket_jugador, tipo_accion); //PUEDE SER DIFERENTE DE CODIGO_JUGAR?
  //   protocolo.recvJugada(socket_jugador, fil, col);
  //
  //   // std::cout << "Recibo Fila -> "  << (int)fil << "||| col -> " << (int)col<< '\n';
  //   partidaActual->jugar(tipoJugador, fil, col);
  // }
  // monitor_partidas.eliminarPartida(nombrePartida);
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
