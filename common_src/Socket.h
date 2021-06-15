#ifndef _SOCKET_H
#define _SOCKET_H

#include <iostream>
#include <string>
#include "ExcepcionSocket.h"

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error, del tipo ExcepcionSocket

class Socket{
  private:
    int fd;

  public:
    /*
    * Constructor
    */
    Socket();

    /*
     * Dado un puerto y un servicio, crea el socket y establece la
     * conexion con el servidor
     */
    void connect(const std::string& host,const std::string& service);

    /*
    * Enlaza el socket con el port
    */
    void bind(const std::string& port);

    /*
    * Crea una cola de espera de long 10
    *para quienes esperan ser atendidos
    */
    void listen();

    /*
    *  Acepta la conexion para la addr dada
    */
    Socket accept() const;

    /*
    * Destruye el socket si el fd es distinto de -1
    * Deja el fd en -1
    */
    void close();

    /*
    * Cierra la comunicacion
    */
    void shutdown();

    /*
    * Envia mensaje de tamanio size de lo que hay en buf
    */
    int sendMsg(const char* buf, const int& size);

    /*
    * Recive size bytes y los almacena en buf
    */
    int recvMsg(char* buf, const int& size);

    /*
    * Constructor por movimiento
    */
    Socket(Socket&& other);

    /*
    * operador asignacion por movimiento
    */
    Socket& operator=(Socket&& other);

    /*
    * Destructor
    */
    ~Socket();

  private:
    /*
    * Constructor, asigna al socket el fd recibido
    * como parametro
    */
    explicit Socket(int fd);
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
};

#endif
