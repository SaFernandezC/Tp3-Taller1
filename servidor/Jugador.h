#ifndef _JUGADOR_H
#define _JUGADOR_H

#include <atomic>
#include "Thread.h"
#include "MonitorPartidas.h"
#include "../common/Socket.h"
#include "../common/Protocolo.h"

class Jugador: public Thread{

  private:
    Socket socket_jugador;
    MonitorPartidas& monitor_partidas;
    Partida* partidaActual;
    char tipoJugador;
    std::atomic<bool> estaCorriendo;

  public:

    Jugador(Socket player_sock, MonitorPartidas& monitor);

    virtual void run() override;

    bool corriendo() const;

    void stop();

    ~Jugador();

  private:
    bool crear_partida(Protocolo& protocolo);
    bool unirse_partida(Protocolo& protocolo);
    void listar_partidas(Protocolo& protocolo);
    void entrarAPartida(Protocolo& protocolo);
    void jugarPartida(Protocolo& protocolo);
};

#endif
