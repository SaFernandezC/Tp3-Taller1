#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../common_src/Protocolo.h"
#include "../common_src/Socket.h"
#include "Analizador.h"
#include <string>

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error

class Cliente{
  private:
    Socket socketCliente;

  public:
    /*
    * Constructor. Crea el socket pasandole el host y port
    * a cual debe conectarse.
    */
    Cliente(const std::string& host, const std::string& port);

    /*
    * Ejecuta el cliente. Crea un analizador y un protocolo
    * para realizar las jugadas.
    */
    void run();

    /*
    * Destructor
    */
    ~Cliente();

  private:
    /*
    * Dentro de esta funcion se realiza un loop hasta que el
    *cliente se une a una partida
    */
    void conectarAPartida(Protocolo& protocolo, Analizador& analizador);

    /*
    * Dentro de esta funcion se realiza un loop mientras
    * se juega la partida y no hay ganador.
    */
    void jugar(Protocolo& protocolo, Analizador& analizador);

    Cliente(const Cliente&)=delete;
    Cliente& operator=(const Cliente&)=delete;
};

#endif
