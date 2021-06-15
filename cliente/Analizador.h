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

class Analizador{
  public:
    Analizador();

    char obtenerAccion(const std::string& jugada);

    void obtenerFilaYCol(const std::string& jugada, char& col, char& fil);

    void verificarIngreso(char& col, char& fil);

    std::string obtenerNombre(const std::string& jugada, const int& pos);

    bool partidaFinalizada(const std::string& tablero);

    ~Analizador();
};

#endif
