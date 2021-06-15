#ifndef _ANALIZADOR_H
#define _ANALIZADOR_H

#include <string>
#include <iostream>
#include "ExcepcionCliente.h"

#define CODIGO_JUGAR 0x70
#define CODIGO_LISTAR 0x6C
#define CODIGO_CREAR 0x6E
#define CODIGO_UNIRSE 0x6A
#define CODIGO_NO_VALIDO 0x6F //Definido por mi

//Todos los metodos lanzan las excepciones correspondientes
//en caso de error

class Analizador{
  public:
    /*
    * Constructor
    */
    Analizador();

    /*
    * A partir de la jugada devuelve el codigo correspondiente
    * a la accion ingresada
    */
    char obtenerAccion(const std::string& jugada);

    /*
    * A partir de la jugada devuelve carga la fila y la columna
    * en las referencias que recibe por parametro
    */
    void obtenerFilaYCol(const std::string& jugada, char& col, char& fil);

    /*
    * Chequea que la col y la fil ingresadas estan dentro
    * de los rangos validos
    */
    void verificarIngreso(const char& col, const char& fil);

    /*
    * A partir de la jugada (crear o unirse) devuelve el nombre
    * de la partida;
    */
    std::string obtenerNombre(const std::string& jugada, const int& pos);

    /*
    * Devuelve true si en el string que representa el tablero
    * hay agluna de las frases de finalizacion de partida.
    */
    bool partidaFinalizada(const std::string& tablero);

    /*
    * Destructor
    */
    ~Analizador();

  private:
    Analizador(const Analizador&) = delete;
    Analizador& operator=(const Analizador&) = delete;
};

#endif
