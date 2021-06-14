#ifndef _TATETI_H
#define _TATETI_H

#define JUGADOR_X 'X'
#define JUGADOR_O 'O'

#include <string>

class Tateti{

  private:
    char tablero[3][3];
    bool ganador;


  public:

    Tateti();

    void realizarJugada(char& caracter, int fil, int col);

    std::string obtenerTablero();

    bool hay_ganador(){
      return ganador;
    }

    ~Tateti();

  private:
    void construirTablero(std::string& auxiliar);
};

#endif
